#ifndef PROCFS_UTILS

#define PROCFS_UTILS
#define PID_MAX_STR_LENGTH 64
#define SIZE_OF_ADDRESS 12
#define MAX_LINE_LENGTH 1024

long procfs_find_executable_region_start_address(long pid);
long procfs_find_executable_region_end_address(long pid);
long procfs_get_stack_pointer(long pid);
long procfs_get_stack_return_address(long stack_address, long pid,
                                     long text_address, long text_size);

#endif
