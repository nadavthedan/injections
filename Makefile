CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRCDIR = src
OBJDIR = obj
INCDIR = include
BINDIR = bins

# Remote process injection (ptrace)
REMOTE_SRC = $(wildcard $(SRCDIR)/remote_process_injection/*.c)
REMOTE_OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(REMOTE_SRC))
REMOTE_BIN = $(BINDIR)/remote_process_injection
REMOTE_CFLAGS = $(CFLAGS) -Iinclude/remote_process_injection

# LD_PRELOAD injection
LD_PRELOAD_SRC = $(wildcard $(SRCDIR)/ld_preload_injection/*.c)
LD_PRELOAD_OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(LD_PRELOAD_SRC))
LD_PRELOAD_BIN = $(BINDIR)/ld_preload_injection
LD_PRELOAD_CFLAGS = $(CFLAGS) -Iinclude/ld_preload_injection

all: remote_process_injection ld_preload_injection

remote_process_injection: $(REMOTE_BIN)

ld_preload_injection: $(LD_PRELOAD_BIN)

# Remote process injection binary
$(REMOTE_BIN): $(REMOTE_OBJ) | $(BINDIR)
	$(CC) $(REMOTE_OBJ) -o $@

$(OBJDIR)/remote_process_injection/%.o: $(SRCDIR)/remote_process_injection/%.c | $(OBJDIR)
	$(CC) $(REMOTE_CFLAGS) -c $< -o $@

# LD_PRELOAD injector binary
$(LD_PRELOAD_BIN): $(LD_PRELOAD_OBJ) | $(BINDIR)
	$(CC) $(LD_PRELOAD_OBJ) -o $@

$(OBJDIR)/ld_preload_injection/%.o: $(SRCDIR)/ld_preload_injection/%.c | $(OBJDIR)
	$(CC) $(LD_PRELOAD_CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)/remote_process_injection $(OBJDIR)/ld_preload_injection

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean remote_process_injection ld_preload_injection
