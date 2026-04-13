#ifndef HT_H
#define HT_H

#include "types.h"

#define CLAY_HT_INIT_CAPACITY 256
#define HT_PRIME_1 1111111111
#define HT_PRIME_2 1111111117

// Hash Table for string : string relation
typedef struct {
  u8 *key;
  u8 *value;
} _clay_ht_item;

typedef struct {
  size_t capacity;
  size_t size;
  _clay_ht_item **items;
} clay_ht;

// ... ht functions
//
clay_ht *clay_ht_init();
void clay_ht_free(clay_ht *ht);
static _clay_ht_item *_clay_ht_new_item(const u8 *key, const u8 *value);
static void _clay_ht_free_item(_clay_ht_item *item);
void clay_ht_insert(clay_ht *ht, const u8 *key, const u8 *value);
u8 *clay_ht_search(clay_ht *ht, const u8 *key);
void clay_ht_delete(clay_ht *ht, const u8 *key);

#endif
