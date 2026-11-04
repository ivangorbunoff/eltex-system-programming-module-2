CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

TARGET = phonebook_static
LIBRARY = libcontacts.a

APP_OBJECTS = main.o ui.o
LIB_OBJECTS = contacts.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(APP_OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) $(APP_OBJECTS) -L. -lcontacts -o $(TARGET)

$(LIBRARY): $(LIB_OBJECTS)
	ar rcs $(LIBRARY) $(LIB_OBJECTS)

main.o: main.c contacts.h ui.h
	$(CC) $(CFLAGS) -c main.c

ui.o: ui.c ui.h contacts.h
	$(CC) $(CFLAGS) -c ui.c

contacts.o: contacts.c contacts.h
	$(CC) $(CFLAGS) -c contacts.c

clean:
	rm -f $(APP_OBJECTS) $(LIB_OBJECTS) $(LIBRARY) $(TARGET)