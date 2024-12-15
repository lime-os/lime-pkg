# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lcurl -lncurses -lcjson

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = include

# Source and Object Files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Target Executable
TARGET = pkg

# Debugging
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g
endif

# Build Rules
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Create Object Directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(TARGET)
