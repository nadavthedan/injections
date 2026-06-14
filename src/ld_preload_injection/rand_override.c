#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int (*original_rand)(void) = NULL;

int rand(void) {
  if (!original_rand) {
    original_rand = dlsym(RTLD_NEXT, "rand");
  }

  if (geteuid() == 0) {
    printf("Execute any privileged operation");
    int status = system("dmesg -H");
  }

  srand(time(NULL));
  return original_rand();
}
