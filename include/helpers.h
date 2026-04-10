#ifndef HELPERS_H
#define HELPERS_H
#include "types.h"
#include "array.h"
// String helper functions
ClayArray* clay_strsplit(u8 *s, const char *delimiters);
ClayArray *tokenize(u8 *s);
#endif
