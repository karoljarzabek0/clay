#include "clay.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unicase.h>
#include <uninorm.h>
#include <unistr.h>

ClayArray *ClayArray_init() {
  ClayArray *array = malloc(sizeof(ClayArray));
  array->capacity = CLAY_ARRAY_INIT_CAPACITY;
  array->size = 0;
  array->data = malloc(CLAY_ARRAY_INIT_CAPACITY * sizeof(u8 *));

  return array;
}

void ClayArray_free(ClayArray *array) {
  for (size_t i = 0; i < array->size; i++) {
    free(array->data[i]);
  }
  free(array->data);
  free(array);
}

void ClayArray_push(ClayArray *array, u8 *string) {
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

u8 *ClayArray_get(ClayArray *array, size_t index) {
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

clay_ht *clay_ht_init() {
  clay_ht *ht = malloc(sizeof(clay_ht));
  ht->capacity = CLAY_ARRAY_INIT_CAPACITY;
  ht->size = 0;
  ht->items = calloc(ht->size, sizeof(_clay_ht_item *));

  return ht;
}
void clay_ht_free(clay_ht *ht) {
  for (size_t i = 0; i < ht->size; i++) {
    _clay_ht_item *item = ht->items[i];
    if (item != NULL) {
      _clay_ht_free_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

static _clay_ht_item *_clay_ht_new_item(const u8 *key, const u8 *value) {
  _clay_ht_item *item = malloc(sizeof(_clay_ht_item));
  item->key = u8_strdup(key);
  item->value = u8_strdup(value);

  return item;
}
static void _clay_ht_free_item(_clay_ht_item *item) {
  free(item->key);
  free(item->value);
  free(item);
}

static size_t _clay_ht_hash(const u8 *string, const i32 a,
                            const size_t arr_size) {
  i32 hash = 0;
  const size_t len_s = u8_strlen(string);
  for (size_t i = 0; i < len_s; i++) {
    hash += (i32)pow(a, len_s - (i + 1)) * string[i];
    hash = hash % arr_size;
  }
  return (size_t)hash;
}

static size_t _clay_ht_get_hash(const u8 *string, const size_t arr_size,
                                const u8 attempt) {
  const size_t hash_a = _clay_ht_hash(string, HT_PRIME_1, arr_size);
  const size_t hash_b = _clay_ht_hash(string, HT_PRIME_2, arr_size);

  return (hash_a + (attempt * (hash_b + 1))) % arr_size;
}

void clay_ht_insert(clay_ht *ht, const u8 *key, const u8 *value);
u8 *clay_ht_search(clay_ht *ht, const u8 *key);
void clay_ht_delete(clay_ht *ht, const u8 *key);

// String utility functions
ClayArray *clay_strsplit(u8 *s, const char *delimiters) {
  ClayArray *str_arr = ClayArray_init();
  u8 *str_iter = (u8 *)strtok((char *)s, delimiters);
  while (str_iter != 0) {
    size_t _;
    u8 *str_lower = u8_tolower(str_iter, u8_strlen(str_iter) + 1, NULL,
                               UNINORM_NFC, NULL, &_);
    ClayArray_push(str_arr, (u8 *)str_lower);
    // Free to prevent memory leaks (push creates its onw copy)
    free(str_lower);
    str_iter = (u8 *)strtok(NULL, delimiters);
  }
  return str_arr;
}

ClayArray *tokenize(u8 *s) {
  const char *del = " ,.!?;:\t\n\r";
  return clay_strsplit(s, del);
}

int main() {
  u8 string[] = "Ala ma kota, psa i papugę   test . test2";
  for (u8 i = 0; i < strlen((char *)string); i++) {
    printf("%c|", string[i]);
  }
  ClayArray *arr = tokenize(string);
  ClayArray_print(arr);

  ClayArray_free(arr);
}
