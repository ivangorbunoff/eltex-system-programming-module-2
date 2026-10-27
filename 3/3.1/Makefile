CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

TARGET = permissions
OBJECTS = main.o permissions.o ui.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

main.o: main.c permissions.h ui.h
	$(CC) $(CFLAGS) -c main.c

permissions.o: permissions.c permissions.h
	$(CC) $(CFLAGS) -c permissions.c

ui.o: ui.c ui.h permissions.h
	$(CC) $(CFLAGS) -c ui.c

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean