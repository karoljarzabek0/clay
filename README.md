# Clay - C playground library

## Goal
This project is an attempt to create a simple to use library with common data structures and helper functions that will speed up the development of other projects.

## Contents
Currently the project contains
- working generic dynamic array implemented with void pointers (resizing is not yet supported) [src/array.c](src/array.c)
- a sketch of open adressed hash table (not working yet) [src/ht.c](src/ht.c)
- helpers functions for string manipulation (like text tokenization) [src/helpers.c](src/helpers.c)
- a sketch of a trie tree for efficient string compression (not working yet) [src/trie.c](src/trie.c)

## Plans
- make a working trie tree prototype for UTF-8 encoded string in the Polish character set
- finish the hashtable
- create a radix tree based on the trie

## Distrubution
I plan to share the library as a precompilded ynamic .so and static .a library with domain scoped headers (like '#include "clay/array.h')
