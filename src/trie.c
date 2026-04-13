#include "types.h"
#include "array.h"
#include "helpers.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistr.h>


/// Maps a lowercase letter to its strict Polish alphabetical index (0-34).
/// Returns -1 for invalid or unsupported characters.
u8 clay_map_codepoint_to_index(ucs4_t cp) {
    switch (cp) {
        case 'a':    return 0;
        case 0x0105: return 1;  // ą
        case 'b':    return 2;
        case 'c':    return 3;
        case 0x0107: return 4;  // ć
        case 'd':    return 5;
        case 'e':    return 6;
        case 0x0119: return 7;  // ę
        case 'f':    return 8;
        case 'g':    return 9;
        case 'h':    return 10;
        case 'i':    return 11;
        case 'j':    return 12;
        case 'k':    return 13;
        case 'l':    return 14;
        case 0x0142: return 15; // ł
        case 'm':    return 16;
        case 'n':    return 17;
        case 0x0144: return 18; // ń
        case 'o':    return 19;
        case 0x00F3: return 20; // ó
        case 'p':    return 21;
        case 'q':    return 22; // Loanword letter
        case 'r':    return 23;
        case 's':    return 24;
        case 0x015B: return 25; // ś
        case 't':    return 26;
        case 'u':    return 27;
        case 'v':    return 28; // Loanword letter
        case 'w':    return 29;
        case 'x':    return 30; // Loanword letter
        case 'y':    return 31;
        case 'z':    return 32;
        case 0x017A: return 33; // ź
        case 0x017C: return 34; // ż
        default:     return -1; // Unmapped character
    }
}

/// Encodes a UTF-8 libunistring into a ClayArray using the Polish index map.
/// 
/// @param str       The UTF-8 string (libunistring uses uint8_t* for u8 strings).
/// @param byte_len  The length of the string in bytes.
/// @param out_array Pointer to the initialized ClayArray to store the results.
void encode_utf8_to_clay_array(const uint8_t *str, size_t byte_len, clay_array *out_array) {
    if (!str || !out_array) return;

    size_t offset = 0;
    
    // Iterate through the UTF-8 string byte by byte
    while (offset < byte_len) {
        ucs4_t codepoint;
        // u8_mbtouc reads the multibyte character at the current offset 
        // and stores it as a ucs4_t codepoint. It returns the number of bytes consumed.
        int bytes_consumed = u8_mbtouc(&codepoint, str + offset, byte_len - offset);

        // If bytes_consumed is <= 0, we hit an invalid sequence or the end of the string
        if (bytes_consumed <= 0) {
            // Optional: Handle encoding error logging here if needed
            break; 
        }

        // Map the extracted codepoint to your Polish index
        int8_t index = clay_map_codepoint_to_index(codepoint);
        
        // Push the resulting index (including -1 for unmapped chars) to the array
        if (index == -1) {
          fprintf(stderr, "Mapping for some char failed\n");
        } else {
        u8 *mangled_index = malloc(sizeof(u8));
        *mangled_index = index;
        clay_array_push(out_array, mangled_index);
        }

        // Advance the offset by however many bytes that UTF-8 character took
        offset += bytes_consumed;
    }
}

/// Maps a strict Polish alphabetical index (0-34) back to a ucs4_t codepoint.
/// Returns 0xFFFD (Unicode Replacement Character) for invalid indices.
ucs4_t clay_map_index_to_codepoint(u8 index) {
    // Lookup table mirroring your original switch statement
    static const ucs4_t map[] = {
        'a', 0x0105, 'b', 'c', 0x0107, 'd', 'e', 0x0119, 'f', 'g',
        'h', 'i', 'j', 'k', 'l', 0x0142, 'm', 'n', 0x0144, 'o',
        0x00F3, 'p', 'q', 'r', 's', 0x015B, 't', 'u', 'v', 'w',
        'x', 'y', 'z', 0x017A, 0x017C
    };

    // Prevent out-of-bounds access
    if (index > 34) {
        return 0xFFFD; 
    }
    
    return map[index];
}
///
/// Decodes a ClayArray of indices back into a UTF-8 string.
///
/// @param in_array       Pointer to the ClayArray containing u8* indices.
/// @param array_len      The number of elements currently in the ClayArray.
/// @param out_byte_len   Pointer to store the final string byte length.
/// @return               A newly allocated uint8_t* containing the UTF-8 string. 
///                       The caller is responsible for freeing this memory.
uint8_t *decode_clay_array_to_utf8(clay_array *in_array, size_t array_len, size_t *out_byte_len) {
    if (!in_array || array_len == 0) {
        if (out_byte_len) *out_byte_len = 0;
        return NULL;
    }

    // Worst-case scenario: each codepoint takes up to 4 bytes in UTF-8.
    // We allocate array_len * 4 + 1 for the null terminator.
    uint8_t *result_str = malloc(array_len * 4 + 1);
    if (!result_str) return NULL;

    size_t offset = 0;

    for (size_t i = 0; i < array_len; i++) {
        // Retrieve the u8* pointer from the array. 
        u8 *index_ptr = (u8 *)clay_array_get(in_array, i); 
        if (!index_ptr) continue;

        // Dereference to get the 0-34 index
        u8 index = *index_ptr;
        
        // Map back to the UCS4 codepoint
        ucs4_t codepoint = clay_map_index_to_codepoint(index);

        if (codepoint == 0xFFFD) {
            // Optional: Skip or handle unmapped/invalid characters
            continue;
        }

        // u8_uctomb converts the ucs4_t codepoint back to UTF-8 bytes.
        // It returns the number of bytes written to the buffer.
        int bytes_written = u8_uctomb(result_str + offset, codepoint, 4);
        if (bytes_written > 0) {
            offset += bytes_written;
        }
    }

    result_str[offset] = '\0'; // Null-terminate for safety
    
    if (out_byte_len) {
        *out_byte_len = offset;
    }

    return result_str;
}

typedef struct TrieNode {
  struct TrieNode *children[32];
} TrieNode;

int main() { 
  u8 *s = (u8*)strdup("Prawną i techniczną odpowiedzialność za Wikisłownik ponosi Fundacja Wikimedia.");
  clay_array *tok_s = tokenize(s);
  for (size_t i = 0; i < tok_s->size; i++) {
    clay_array *temp_arr = clay_array_init();
    u8 *word = clay_array_get(tok_s, i);
    encode_utf8_to_clay_array(word, u8_strlen(word), temp_arr);

    printf("----------\n");
    for (size_t j = 0; j < temp_arr->size; j++) {
        u8 *idx_ptr = clay_array_get(temp_arr, j);
        if (idx_ptr) {
            printf("%zu: %d | ", j, *idx_ptr);
        }
    }
    printf("\n");
    printf("Word: %s\n", word);
    clay_array_free(temp_arr);
  }
}
