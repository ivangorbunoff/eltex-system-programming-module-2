CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

TARGET = calculator_plugins
OBJECTS = main.o

PLUGIN_DIR = plugins
OPERATION_DIR = operations

LIB = $(addprefix $(PLUGIN_DIR)/, libadd.so libsubtract.so libmultiply.so libdivide.so)

.PHONY: all lib run clean

all: $(TARGET) lib

lib: $(LIB)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -ldl -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

$(PLUGIN_DIR)/libadd.so: $(OPERATION_DIR)/add.c
	$(CC) $(CFLAGS) -fPIC -shared $(OPERATION_DIR)/add.c -o $(PLUGIN_DIR)/libadd.so

$(PLUGIN_DIR)/libsubtract.so: $(OPERATION_DIR)/subtract.c
	$(CC) $(CFLAGS) -fPIC -shared $(OPERATION_DIR)/subtract.c -o $(PLUGIN_DIR)/libsubtract.so

$(PLUGIN_DIR)/libmultiply.so: $(OPERATION_DIR)/multiply.c
	$(CC) $(CFLAGS) -fPIC -shared $(OPERATION_DIR)/multiply.c -o $(PLUGIN_DIR)/libmultiply.so

$(PLUGIN_DIR)/libdivide.so: $(OPERATION_DIR)/divide.c
	$(CC) $(CFLAGS) -fPIC -shared $(OPERATION_DIR)/divide.c -o $(PLUGIN_DIR)/libdivide.so

run: all
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) $(LIB)
