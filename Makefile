CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lcurl -lncurses -lcjson

SRC = src/main.c src/utils.c src/search.c src/menu.c src/install.c
OBJ = $(SRC:.c=.o)

TARGET = pkg

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
