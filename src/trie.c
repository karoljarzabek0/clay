#include "types.h"
#include "array.h"
#include <stddef.h>
#include <stdio.h>
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

ClayArray* clay_ustring_to_mapped_array(const u8 *s, size_t byte_len) {

}



typedef struct TrieNode {
  struct TrieNode *children[32];
} TrieNode;

int main() { printf("Hello, Trie!"); }
