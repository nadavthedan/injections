#define _GNU_SOURCE
#include "procfs_utils.h"
#include <sys/uio.h>

int process_vm_writev_write(long pid, long address, void *data, int data_len) {
  struct iovec local[1];
  struct iovec remote[1];

  local[0].iov_base = data;
  local[0].iov_len = data_len;

  remote[0].iov_base = (void *)address;
  remote[0].iov_len = data_len;

  process_vm_writev(pid, local, 1, remote, 1, 0);

  return 0;
}

int process_vm_writev_stack_overwrite_exec(long pid, long address) {
  long stack_pointer = procfs_get_stack_pointer(pid);

  long text_section_start = procfs_find_executable_region_start_address(pid);
  long text_section_end = procfs_find_executable_region_end_address(pid);

  long text_section_size = text_section_end - text_section_start;

  long stack_ret_address = procfs_get_stack_return_address(
      stack_pointer, pid, text_section_start, text_section_size);

  process_vm_writev_write(pid, stack_ret_address, &address, sizeof(long));

  return 0;
}
