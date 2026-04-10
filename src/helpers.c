#include "types.h"
#include "array.h"
#include <unistr.h>
#include <unicase.h>
#include <string.h>
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


