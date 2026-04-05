#include "clay.h"
#include <string.h>
#include <unicase.h>
#include <uninorm.h>
#include <unistr.h>



ClayArray* ClayArray_init() {
  ClayArray *array = malloc(sizeof(ClayArray));
  array->capacity = CLAY_ARRAY_INIT_CAPACITY;
  array->size = 0;
  array->data = malloc(CLAY_ARRAY_INIT_CAPACITY * sizeof(u8*));

  return array;
}

void ClayArray_free(ClayArray *array) {
  for(size_t i = 0; i < array->size; i++) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}

void ClayArray_push(ClayArray *array, u8 *string) {
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

u8* ClayArray_get(ClayArray* array, size_t index) {
  if (array->size <= index) {
    fprintf(stderr, "Error: tried to access out of bound array element\n");
    exit(EXIT_FAILURE);
  } else {
    return array->data[index];
  }
}

void ClayArray_print(ClayArray *array) {
  for (size_t i = 0; i < array->size; i++) {
    fprintf(stdout, "%zu: %s\n", i, array->data[i]);
  }
}

// String utility functions
ClayArray* clay_strsplit(u8 *s, const char *delimiters) {
  ClayArray *str_arr = ClayArray_init();
  u8 *str_iter = (u8*) strtok((char*)s, delimiters);
  while (str_iter != 0) {
    size_t _;
    u8 *str_lower = u8_tolower(str_iter, u8_strlen(str_iter) + 1, NULL, UNINORM_NFC, NULL, &_);
    ClayArray_push(str_arr, (u8*) str_lower);
    // Free to prevent memory leaks (push create its onw copy)
    free(str_lower);
    str_iter = (u8*) strtok(NULL, delimiters);
  }

  return str_arr;
}

int main() {
  u8 string[] = "Ala ma kota, psa i papugę   test . test2";
  ClayArray* arr = clay_strsplit(string, " ,.!?;:\t\n\r");
  ClayArray_print(arr);

  ClayArray_free(arr);
}
