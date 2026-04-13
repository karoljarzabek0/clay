#ifndef ARRAY_H
#define ARRAY_H
#include <unistr.h>
#include "types.h"


#define CLAY_ARRAY_INIT_CAPACITY 256

// Dynamic array of null-terminated strings
typedef struct {
  size_t capacity;
  size_t size;
  u8 **data;
} clay_array;

// Initializes the array
clay_array* clay_array_init();
// Frees the array
void clay_array_free(clay_array *a);
// Helper function
// ClayArray* _ClayArray_resize(ClayArray* a, size_t new_cap);
// Add a string at the end of the array
void clay_array_push(clay_array *a, u8 *s);
// Get string at a given index
u8* clay_array_get(clay_array *a, size_t i);
void clay_array_print(clay_array *array); 

#endif
