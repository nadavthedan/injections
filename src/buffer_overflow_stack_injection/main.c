#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  volatile int modified = 0;
  char buffer[8];

  if (argc < 2) {
    printf("Pass an argument.\n");
    return 1;
  }

  strcpy(buffer, argv[1]);

  if (modified != 0) {
    printf("SUCCESS: The memory was manipulated. modified is: %d\n", modified);
  } else {
    printf("FAILED: The memory was not manipulated.\n");
  }
  return 0;
}
