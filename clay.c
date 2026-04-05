#include "clay.h"



ClayArray* ClayArray_init(size_t init_cap) {
  ClayArray *array = malloc(sizeof(ClayArray));
  array->capacity = init_cap;
  array->size = 0;
  array->data = malloc(init_cap * sizeof(u8*));

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
ClayArray* clay_strsplit(u8 *s, char delimiter);
