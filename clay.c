#include "clay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unicase.h>
#include <uninorm.h>
#include <unistr.h>



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

////////////////////////////////////////////
/// HashTable
/// ///////////////////////////////////////


clay_ht* clay_ht_init() {
  clay_ht *ht = malloc(sizeof(clay_ht));
  ht->capacity = CLAY_ARRAY_INIT_CAPACITY;
  ht->size = 0;
  ht->items = calloc(ht->size, sizeof(_clay_ht_item*));

  return ht;
}
void clay_ht_free(clay_ht *ht);
static _clay_ht_item* _clay_ht_new_item(const u8 *key, const u8 *value);
static void _clay_ht_free_item(const u8 *key);
void clay_ht_insert(clay_ht *ht, const u8 *key, const u8 *value);
u8* clay_ht_search(clay_ht *ht, const u8 *key);
void clay_ht_delete(clay_ht *ht, const u8 *key);


// String utility functions
ClayArray* clay_strsplit(u8 *s, const char *delimiters) {
  ClayArray *str_arr = ClayArray_init();
  u8 *str_iter = (u8*) strtok((char*)s, delimiters);
  while (str_iter != 0) {
    size_t _;
    u8 *str_lower = u8_tolower(str_iter, u8_strlen(str_iter) + 1, NULL, UNINORM_NFC, NULL, &_);
    ClayArray_push(str_arr, (u8*) str_lower);
    // Free to prevent memory leaks (push creates its onw copy)
    free(str_lower);
    str_iter = (u8*) strtok(NULL, delimiters);
  }
  return str_arr;
}

ClayArray* tokenize(u8 *s) {
  const char *del = " ,.!?;:\t\n\r"; 
  return clay_strsplit(s, del);
}

int main() {
  u8 string[] = "Ala ma kota, psa i papugę   test . test2";
  for (u8 i = 0; i < strlen((char*)string); i++) {
    printf("%c|", string[i]);
  }
  ClayArray* arr = tokenize(string);
  ClayArray_print(arr);

  ClayArray_free(arr);
}
