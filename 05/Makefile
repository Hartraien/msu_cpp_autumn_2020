CC = g++

CFLAGS = -std=c++17 -g -Wall -O1

VPATH = ./src:./test

all: test.out

test: test.out
	./test.out

test.out: test.cpp Serializer.o Deserializer.o
	$(CC) $(CFLAGS) $^ -o $@

Serializer.o: Serializer.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

Deserializer.o: Deserializer.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.out