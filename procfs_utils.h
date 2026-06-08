#ifndef PROCFS_UTILS

#define PROCFS_UTILS
#define PID_MAX_STR_LENGTH 64
#define SIZE_OF_ADDRESS 12

long procfs_find_executable_region_start_address(long pid);

#endif
