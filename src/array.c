#include "array.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

clay_array* clay_array_init() {
  clay_array *array = malloc(sizeof(clay_array));
  array->capacity = CLAY_ARRAY_INIT_CAPACITY;
  array->size = 0;
  array->data = malloc(CLAY_ARRAY_INIT_CAPACITY * sizeof(void*));
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

// Accept a function pointer that takes a void* and knows how to print it
void clay_array_print(clay_array *array, void (*print_element)(void *)) {
  for (size_t i = 0; i < array->size; i++) {
    fprintf(stdout, "%zu: ", i);   // %zu is the correct format specifier for size_t
    print_element(array->data[i]); // Call the custom print function
    fprintf(stdout, "\n");
  }
}

// Helper function to print an integer
void print_int(void *element) {
  // Cast the void* back to an int* and dereference it
  int *val = (int *)element;
  printf("%d", *val);
}

// Helper function to print a string
void print_string(void *element) {
  // Cast the void* to a char*
  char *str = (char *)element;
  printf("%s", str);
}
