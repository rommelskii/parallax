# 1. Compiler and Flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
LDLIBS = -luuid # ADD THIS LINE for linker libraries

# 2. Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# 3. Executable Name
TARGET = $(BINDIR)/prlx

# 4. Find all .c files in the source directory
SOURCES = $(wildcard $(SRCDIR)/*.c)

# 5. Create a list of corresponding object files in the obj directory
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# --- Rules ---

all: $(TARGET)

# Rule to link the final executable.
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
ifeq ($(shell uname -s),Linux)
		$(CC) $(OBJECTS) -o $(TARGET) $(LDLIBS)
else 
		$(CC) $(OBJECTS) -o $(TARGET) 
endif
	@echo "Linking complete. Executable is at $(TARGET)"

# Rule to compile a .c file into a .o file.
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< into $@"

clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "Cleaned build artifacts."

run: all
	./$(TARGET) $(ARGS)

.PHONY: all clean run

