#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistr.h>
#include <unicase.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

#define CLAY_ARRAY_INIT_CAPACITY 256
#define CLAY_HT_INIT_CAPAACITY 256

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
  u8 *key;
  u8 *value;
} _clay_ht_item;

typedef struct {
  size_t capacity;
  size_t size;
  _clay_ht_item** items;
} clay_ht;

// ... ht functions
//
clay_ht* clay_ht_init();
void clay_ht_free(clay_ht *ht);
static _clay_ht_item* _clay_ht_new_item(const u8 *key, const u8 *value);
static void _clay_ht_free_item(const u8 *key);
void clay_ht_insert(clay_ht *ht, const u8 *key, const u8 *value);
u8* clay_ht_search(clay_ht *ht, const u8 *key);
void clay_ht_delete(clay_ht *ht, const u8 *key);

// String helper functions
ClayArray* clay_strsplit(u8 *s, const char *delimiters);



