CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

UNITY_DIR = ../../third_party/unity
TEST_TARGET = tests/test_priority_queue
TEST_SOURCES = tests/test_priority_queue.c priority_queue.c $(UNITY_DIR)/unity.c

all: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES) priority_queue.h
	$(CC) $(CFLAGS) -I. -I$(UNITY_DIR) $(TEST_SOURCES) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET)

.PHONY: all test clean
