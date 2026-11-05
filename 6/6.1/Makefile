CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

APP_DIR = app
LIB_DIR = library

TARGET = phonebook_static
LIBRARY = $(LIB_DIR)/libcontacts.a

APP_OBJECTS = $(APP_DIR)/main.o $(APP_DIR)/ui.o
LIB_OBJECTS = $(LIB_DIR)/contacts.o

.PHONY: all library clean

all: $(TARGET)

library: $(LIBRARY)

$(TARGET): $(APP_OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) $(APP_OBJECTS) -L$(LIB_DIR) -lcontacts -o $(TARGET)

$(LIBRARY): $(LIB_OBJECTS)
	ar rcs $(LIBRARY) $(LIB_OBJECTS)

$(APP_DIR)/main.o: $(APP_DIR)/main.c $(APP_DIR)/ui.h $(LIB_DIR)/contacts.h
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $(APP_DIR)/main.c -o $(APP_DIR)/main.o

$(APP_DIR)/ui.o: $(APP_DIR)/ui.c $(APP_DIR)/ui.h $(LIB_DIR)/contacts.h
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $(APP_DIR)/ui.c -o $(APP_DIR)/ui.o

$(LIB_DIR)/contacts.o: $(LIB_DIR)/contacts.c $(LIB_DIR)/contacts.h
	$(CC) $(CFLAGS) -c $(LIB_DIR)/contacts.c -o $(LIB_DIR)/contacts.o

clean:
	rm -f $(APP_OBJECTS) $(LIB_OBJECTS) $(LIBRARY) $(TARGET)
