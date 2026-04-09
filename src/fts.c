// I need:
// Tokenization - dynamic array of strings
// Stopwords - string string hashmap or a trie
// inverted index - string size_t hashmap
// index + (word to id) and odcmap (id to doc)
//
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Doc {
	size_t id;
	size_t length;
	uint8_t **content;
} Doc;
	

