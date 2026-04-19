#include "array.h"
#include "helpers.h"
#include <string.h>
int main() {
  u8 *s = (u8*)strdup("Prawną i techniczną odpowiedzialność za Wikisłownik ponosi Fundacja Wikimedia.");
  clay_array *tokens = tokenize(s);
  clay_array_print(tokens, print_string);

  clay_array_free(tokens);
  free(s);
  return 0;
}
