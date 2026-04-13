#include "array.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

clay_array *clay_array_init(size_t element_size) {
  clay_array *array = malloc(sizeof(clay_array));
  array->capacity = CLAY_ARRAY_INIT_CAPACITY;
  array->size = 0;
  array->element_size = element_size;
  array->data = malloc(CLAY_ARRAY_INIT_CAPACITY * element_size);

  return array;
}

void clay_array_free(clay_array *array) {
  for (size_t i = 0; i < array->size; i++) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}

void clay_array_push(clay_array *array, void *element) {
  if (array->size + 1 <= array->capacity) {
    array->data[array->size] = element;
    array->size++;

  } else {
    fprintf(stderr, "Error: array full\n");
    exit(EXIT_FAILURE);
  }
}

void *clay_array_get(clay_array *array, size_t index) {
  if (array->size <= index) {
    fprintf(stderr, "Error: tried to access out of bound array element\n");
    exit(EXIT_FAILURE);
  } else {
    return array->data[index];
  }
}

/// Currently broken
void clay_array_print(clay_array *array, const char *fmt) {
  for (size_t i = 0; i < array->size; i++) {
    fprintf(stdout, "%zu: %s\n", i, array->data[i]);
  }
}
