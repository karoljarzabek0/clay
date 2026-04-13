#include "array.h"
#include <stdio.h>
#include <string.h>

clay_array *clay_array_init() {
  clay_array *array = malloc(sizeof(clay_array));
  array->capacity = CLAY_ARRAY_INIT_CAPACITY;
  array->size = 0;
  array->data = malloc(CLAY_ARRAY_INIT_CAPACITY * sizeof(u8 *));

  return array;
}

void clay_array_free(clay_array *array) {
  for (size_t i = 0; i < array->size; i++) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}

void clay_array_push(clay_array *array, u8 *string) {
  if (array->size + 1 <= array->capacity) {
    u8 *new_string = malloc(u8_strlen(string) + 1);
    memcpy(new_string, string, u8_strlen(string) + 1);
    array->data[array->size] = new_string;
    array->size++;

  } else {
    fprintf(stderr, "Error: array full\n");
    exit(EXIT_FAILURE);
  }
}

u8 *clay_array_get(clay_array *array, size_t index) {
  if (array->size <= index) {
    fprintf(stderr, "Error: tried to access out of bound array element\n");
    exit(EXIT_FAILURE);
  } else {
    return array->data[index];
  }
}

void clay_array_print(clay_array *array) {
  for (size_t i = 0; i < array->size; i++) {
    fprintf(stdout, "%zu: %s\n", i, array->data[i]);
  }
}
