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
} ClayArray;

// Initializes the array
ClayArray* ClayArray_init();
// Frees the array
void ClayArray_free(ClayArray *a);
// Helper function
// ClayArray* _ClayArray_resize(ClayArray* a, size_t new_cap);
// Add a string at the end of the array
void ClayArray_push(ClayArray *a, u8 *s);
// Get string at a given index
u8* ClayArray_get(ClayArray *a, size_t i);
void ClayArray_print(ClayArray *array); 

#endif
