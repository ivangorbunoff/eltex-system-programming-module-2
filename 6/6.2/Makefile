CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

APP_DIR = app
LIB_DIR = library

TARGET = phonebook_dynamic
LIBRARY = libcontacts.so

APP_OBJECTS = $(APP_DIR)/main.o $(APP_DIR)/ui.o
LIB_OBJECTS = $(LIB_DIR)/contacts.o

.PHONY: all library run clean

all: $(TARGET)

library: $(LIBRARY)

$(TARGET): $(APP_OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) $(APP_OBJECTS) -L. -lcontacts -o $(TARGET)

$(LIBRARY): $(LIB_OBJECTS)
	$(CC) -shared $(LIB_OBJECTS) -o $(LIBRARY)

$(APP_DIR)/main.o: $(APP_DIR)/main.c $(APP_DIR)/ui.h $(LIB_DIR)/contacts.h
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $(APP_DIR)/main.c -o $(APP_DIR)/main.o

$(APP_DIR)/ui.o: $(APP_DIR)/ui.c $(APP_DIR)/ui.h $(LIB_DIR)/contacts.h
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $(APP_DIR)/ui.c -o $(APP_DIR)/ui.o

$(LIB_DIR)/contacts.o: $(LIB_DIR)/contacts.c $(LIB_DIR)/contacts.h
	$(CC) $(CFLAGS) -fPIC -c $(LIB_DIR)/contacts.c -o $(LIB_DIR)/contacts.o

run: $(TARGET)
	LD_LIBRARY_PATH=$(CURDIR):$$LD_LIBRARY_PATH ./$(TARGET)

clean:
	rm -f $(APP_OBJECTS) $(LIB_OBJECTS) $(LIBRARY) $(TARGET)