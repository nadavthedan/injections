#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_permissions_from_line(char *line) {
  int first_space = -1;
  int second_space = -1;
  for (size_t i = 0; i < strlen(line); i++) {
    if (line[i] == ' ' && first_space == -1) {
      first_space = i + 1;
    } else if (line[i] == ' ' && first_space != -1) {
      second_space = i;
      break;
    }
  }
  if (first_space != -1 && second_space != -1 && second_space > first_space) {
    char *permissions = malloc(second_space - first_space + 1);
    if (permissions == NULL) {
      fprintf(stderr, "Failed malloc.\n");
      return NULL;
    }
    for (size_t i = first_space, j = 0; i < (size_t)second_space; i++, j++) {
      permissions[j] = line[i];
    }
    permissions[second_space - first_space] = '\0';
    return permissions;
  }
  return NULL;
}
