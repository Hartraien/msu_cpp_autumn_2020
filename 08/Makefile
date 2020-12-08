CC = g++

CFLAGS = -std=c++17 -g -Wall -O1

VPATH = ./src:./test

all: test.out

test: test.out
	./test.out

test.out: test.o ThreadPool.o
	$(CC) $(CFLAGS) -pthread $^ -o $@

test.o: test.cpp
	$(CC) $(CFLAGS) -c $< -o $@

ThreadPool.o: ThreadPool.cpp ThreadPool.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf *.out