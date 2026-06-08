#include "procfs_utils.h"
#include <errno.h>
#include <stdbool.h>
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

long get_start_address_from_maps_line(char *line) {
  char *address_line = malloc(SIZE_OF_ADDRESS + 1);
  memset(address_line, 0, SIZE_OF_ADDRESS + 1);
  memcpy(address_line, line, SIZE_OF_ADDRESS);
  long address = strtol(address_line, (char **)NULL, 16);

  return address;
}

long get_end_address_from_maps_line(char *line) {
  char *start_address = strchr(line, '-') + 1;
  char *address_line = malloc(SIZE_OF_ADDRESS + 1);
  memset(address_line, 0, SIZE_OF_ADDRESS + 1);
  memcpy(address_line, start_address, SIZE_OF_ADDRESS);
  long address = strtol(address_line, (char **)NULL, 16);

  return address;
}

long procfs_find_memory_region(long pid, bool get_region_start_address,
                               char *permissions_string) {
  size_t maps_file_name_length = PID_MAX_STR_LENGTH + 12;
  char *maps_file_name = malloc(maps_file_name_length);
  if (snprintf(maps_file_name, maps_file_name_length, "/proc/%ld/maps", pid) <
      0) {
    fprintf(stderr, "Failed snprintf: %s\n", strerror(errno));
    return -1;
  }

  FILE *maps_file = fopen(maps_file_name, "r");
  if (maps_file == NULL) {
    fprintf(stderr, "Failed open for: %s\n", maps_file_name);
    return -1;
  }

  char *maps_line = NULL;
  size_t maps_line_length = 0;
  while (getline(&maps_line, &maps_line_length, maps_file) != -1) {
    char *permissions = get_permissions_from_line(maps_line);

    if (permissions == NULL) {
      continue;
    } else if (strstr(permissions, permissions_string) != NULL) {
      free(permissions);
      break;
    }
    free(permissions);
  }
  long address;
  if (get_region_start_address) {
    address = get_start_address_from_maps_line(maps_line);
  } else {
    address = get_end_address_from_maps_line(maps_line);
  }

  free(maps_line);

  return address;
}

long procfs_find_executable_region_start_address(long pid) {
  return procfs_find_memory_region(pid, true, "r-x");
}
