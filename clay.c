#include "clay.h"
#include <string.h>



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
ClayArray* clay_strsplit(u8 *s, char delimiter) {
  ClayArray *str_arr = ClayArray_init();
  char *str_iter = strtok((char*)s, &delimiter);
  while (str_iter != 0) {
    ClayArray_push(str_arr, (u8*) str_iter);
    str_iter = strtok(NULL, &delimiter);
  }

  return str_arr;
}

int main() {
  u8 string[] = "Ala ma kota, psa i papugę";
  ClayArray* arr = clay_strsplit(string, ' ');
  ClayArray_print(arr);
}
