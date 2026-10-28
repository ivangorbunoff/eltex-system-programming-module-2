CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

TARGET = network_simulator
OBJECTS = main.o network.o ui.o

UNITY_DIR = ../../third_party/unity
TEST_TARGET = tests/test_network
TEST_SOURCES = tests/test_network.c network.c $(UNITY_DIR)/unity.c

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

main.o: main.c network.h ui.h
	$(CC) $(CFLAGS) -c main.c

network.o: network.c network.h
	$(CC) $(CFLAGS) -c network.c

ui.o: ui.c ui.h network.h
	$(CC) $(CFLAGS) -c ui.c

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES) network.h
	$(CC) $(CFLAGS) -I. -I$(UNITY_DIR) $(TEST_SOURCES) -o $(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
