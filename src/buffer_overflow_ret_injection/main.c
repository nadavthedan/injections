#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void secret_function() {
  printf("Success: root hijacked.");
  system("/bin/sh");
}

void vulnerabble_function(char *str) {
  char buffer[16];
  strcpy(buffer, str);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return 1;
  }

  vulnerabble_function(argv[1]);
  return 0;
}
