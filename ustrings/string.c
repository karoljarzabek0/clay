#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistdio.h>
#include <unistr.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

size_t u8_codlen(u8 *string) {
    size_t units = u8_strlen(string); 
    size_t codepoints = u8_mbsnlen(string, units);
    return codepoints;
}

typedef struct {
  size_t size;
  size_t capacity;
  u8 **data;
} SDarray;

SDarray* SDarray_new(size_t init_cap) {
  SDarray *array = malloc(sizeof(SDarray));
  array->capacity = init_cap;
  array->size = 0;
  array->data = malloc(init_cap * sizeof(u8*));

  return array;
}

void SDarray_free(SDarray *array) {
  free(array->data);
  free(array);
}

void SDarray_push(SDarray *array, u8 *string);

SDarray* u8_split(u8 *string, char delimiter);

int main() {
  // Cast the string literal to uint8_t* as expected by the library
    uint8_t *string = (uint8_t *)"Aąbćdeę";
    size_t units = u8_strlen(string);
    size_t codepoints = u8_codlen(string);
    
 printf("Len: %zu, Ulen: %zu\n", units, codepoints);
}
