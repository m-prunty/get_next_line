#include <stdlib.h>

int main(void) {
  char *tmp = malloc(10);
  ++tmp;
  free(tmp);
}
