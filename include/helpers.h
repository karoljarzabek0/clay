#ifndef HELPERS_H
#define HELPERS_H
#include "types.h"
#include "array.h"
// String helper functions
clay_array* clay_strsplit(u8 *s, const char *delimiters);
clay_array *tokenize(u8 *s);
#endif
