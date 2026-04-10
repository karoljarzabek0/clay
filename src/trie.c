#include "types.h"
#include <stdio.h>
#include <unistr.h>

u8 clay_map_letter(const u8 *l) {}

typedef struct TrieNode {
  struct TrieNode *children[32];
} TrieNode;

int main() { printf("Hello, Trie!"); }
