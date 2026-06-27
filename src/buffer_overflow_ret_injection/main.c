#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void __attribute__((force_align_arg_pointer)) secret_function() {
  printf("Success: root hijacked.\n");
  fflush(stdout);
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
