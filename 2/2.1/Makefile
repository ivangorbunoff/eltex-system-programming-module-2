CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = phonebook
OBJECTS = main.o contacts.o ui.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.c contacts.h ui.h
	$(CC) $(CFLAGS) -c main.c

contacts.o: contacts.c contacts.h
	$(CC) $(CFLAGS) -c contacts.c

ui.o: ui.c ui.h contacts.h
	$(CC) $(CFLAGS) -c ui.c

clean:
	rm -f $(OBJECTS) $(TARGET)
