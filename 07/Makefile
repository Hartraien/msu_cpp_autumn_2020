CC = g++

CFLAGS = -std=c++17 -g -Wall -O1

VPATH = ./src:./src/exc:./test

all: test.out

test: test.out
	./test.out

test.out: test.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.out