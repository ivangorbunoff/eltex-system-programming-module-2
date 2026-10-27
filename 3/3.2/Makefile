CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

TARGET = network_simulator
OBJECTS = main.o network.o ui.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

main.o: main.c network.h ui.h
	$(CC) $(CFLAGS) -c main.c

network.o: network.c network.h
	$(CC) $(CFLAGS) -c network.c

ui.o: ui.c ui.h network.h
	$(CC) $(CFLAGS) -c ui.c

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
