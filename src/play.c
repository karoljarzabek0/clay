#include "array.h"
#include "helpers.h"
#include <string.h>
int main() {
  u8 *s = (u8*)strdup("Prawną i techniczną odpowiedzialność za Wikisłownik ponosi Fundacja Wikimedia.");
  ClayArray *tokens = tokenize(s);
  ClayArray_print(tokens);

}
