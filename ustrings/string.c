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
  for(size_t i = 0; i < array->size; i++) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}

void SDarray_push(SDarray *array, u8 *string) {
  if (array->size + 1 <= array->capacity){
  u8 *new_string = malloc(u8_strlen(string) + 1);
  memcpy(new_string, string, u8_strlen(string) + 1);
  array->data[array->size] = new_string;
  array->size++;

  } else {
    fprintf(stderr, "Error: array full\n");
    exit(EXIT_FAILURE);
  }
}

u8* SDarray_get(SDarray* array, size_t index) {
  if (array->size <= index) {
    fprintf(stderr, "Error: tried to access out of bound array element\n");
    exit(EXIT_FAILURE);
  } else {
    return array->data[index];
  }
}

void SDarray_print(SDarray *array) {
  for (size_t i = 0; i < array->size; i++) {
    fprintf(stdout, "%zu: %s\n", i, array->data[i]);
  }
}

SDarray* u8_split(u8 *string, char delimiter);

int main() {
  SDarray *darr = SDarray_new(10);
  SDarray_push(darr, (u8*)"test");
  SDarray_push(darr, (u8*)"test1");
  SDarray_push(darr, (u8*)"test2");
  SDarray_push(darr, (u8*)"test3");

  u8 *obt = SDarray_get(darr, 2);
  printf("String at index: %d: %s\n", 2, obt);

  SDarray_print(darr);
}
