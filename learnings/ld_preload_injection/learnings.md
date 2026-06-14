# Preload Injection

This injection is really simple and stright forward.

## What I think are the pros of this injection

- It retains permissions and context of the process.
- Easily written shared objects in c, no need for SHELL_CODE. Has the full power of c.
- Easily attached to specific methods/variables which gives a lot of control.

## What I think are the cons of this injection

- It seems easy to detect and even prevent.
- Requires to have a compiled shared object on the target machine (which I guess could also be easily detected with an antivirus or something).
- Requires to attach the LD_PRELOAD env variable without the user noticing. //TODO: figure out ways to do that.
- Doens't work on static linked binaries.

## Stealth

Because LD_PRELOAD hooks function calls at the user level,
tools like ps, topo or ls can be easily decived
(hook readdir to hide from ls, hook fopen to hide fomr /proc).

When the injected library contains a bug, memory leak or a seg fault, it will affect every binary using the hooked code.
This could cause mass crashes or memory leaks that would alert the system administrator for some malware. (Although I think this the case for most if not all injections).

# SUID/SGID

ld.so has a built-in security mechanism often called "Secure-Execution Mode".
When you execute a program, the kernael checks if the process's Real UID/GID matches its Effective UID/GID (granted by SUID/SGID from the binary).
If they do not match, the kernel marks the process as running in secure-execution mode, which unseats dangerous env vars (including LD_PRELOAD).
Generally most bins are not defined with SUID/SGID mostly bins like passwd/sudo/chsh are defined like that.
Modern Linux development is activly tyring to eliminate SUID bins and replace it with "Capablities".
