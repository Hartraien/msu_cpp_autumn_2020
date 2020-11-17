CC = g++

CFLAGS = -std=c++17 -g -Wall -O1

VPATH = ./src:./test

all: test.out

test: test.out
	./test.out

test.out: test.cpp Formatter.o
	$(CC) $(CFLAGS) $^ -o $@

Formatter.o: Formatter.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.out