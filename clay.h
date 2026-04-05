#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistr.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;


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

// Hash Table for string : string relation

typedef struct {
  size_t capacity;
  size_t size;
  u8 **data;
} ClayTable;

// ... ht functions
//

// String helper functions
ClayArray* clay_strsplit(u8 *s, char delimiter);



