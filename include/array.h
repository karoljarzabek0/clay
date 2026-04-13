#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>
#include <stdio.h>
#include <unistr.h>
#include "types.h"


#define CLAY_ARRAY_INIT_CAPACITY 256

// Dynamic array of null-terminated strings
typedef struct {
  size_t capacity;
  size_t size;
  size_t element_size;
  u8 **data;
} clay_array;

// Initializes the array
clay_array* clay_array_init(size_t element_size);
// Frees the array
void clay_array_free(clay_array *a);
// Helper function
// ClayArray* _ClayArray_resize(ClayArray* a, size_t new_cap);
// Add a string at the end of the array
void clay_array_push(clay_array *array, void *element);
// Get string at a given index
void *clay_array_get(clay_array *array, size_t index);
void clay_array_print(clay_array *array, const char *fmt); 

#endif
