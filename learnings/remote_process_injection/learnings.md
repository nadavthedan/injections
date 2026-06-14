# Remote Process Injection

There are 3 main ways to interact with the memory of remote processes in linux: ptrace, procfs and process_vm_writev.
For this remote process injection I used a combination of ptrace and process_vm_writev just to feel them out.
ptrace doesn't require write permissions while process_vm_writev does (but it is easy to find writable parts of a process memory)

Those techniques didn't really strike me as impressive (at least on their own).

They could only be used if:

- ptrace_scope is 1 or 0 (which isn't the default case most of the time).
- the process dumpable attribute wasn't manually set to false (through prctl).

It is pretty easily detectable through:

- syscall montoring
- process anomalies

It could be used with:

- stack hijacking
- ROP stack hijacking
- GOT hijacking

Though I don't really know if the different hijacks are important and what benefits each has.
I could guess some are more stealthy then others, and some may be more easily detectable then others.
Maybe different hijackings could be useful to inject at different specific states of the code execution.

//TODO: research uses of different types of hijacking.
// Answer:

This also disappointed me when I tried to hijack a privileged process. This is not possible with this method (at least to what I could figure out for now).

What I think this can be used for is stealth, loading shared objects for some purpose and more.

It retains context, that means that if a Process has capabilities you can inherit them.
You also have access to active connections (db connections / api authenticated sessions), and data in the memory of the process.
Although I think this is true to most if not all injections.

A unique thing that is great about it is that it could be used on a already running process.

# Stealth

While this injection could be stealthy and triggered at specific timings and hooks, recovery must be handled really carefully to avoid suspicion or detection.
It is way harder of a recovery then other methods such as hooking with LD_PRELOAD.
Any error in recovery or even in the hijacking itself could crash the process and alert the system admin.
