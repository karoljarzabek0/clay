#include "types.h"
#include "ht.h"
#include <stdlib.h>
#include <unistr.h>
#include <math.h>
////////////////////////////////////////////
/// HashTable
/// ///////////////////////////////////////

clay_ht *clay_ht_init() {
  clay_ht *ht = malloc(sizeof(clay_ht));
  ht->capacity = CLAY_HT_INIT_CAPACITY;
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


