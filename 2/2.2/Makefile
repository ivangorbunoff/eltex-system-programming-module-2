CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = calculator
OBJECTS = main.o calc.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.c calc.h
	$(CC) $(CFLAGS) -c main.c

calc.o: calc.c calc.h
	$(CC) $(CFLAGS) -c calc.c

clean:
	rm -f $(OBJECTS) $(TARGET)
