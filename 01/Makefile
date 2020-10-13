CC = g++

CFLAGS = -std=c++17 -g -Wall

VPATH = ./src:./test

all: Allocator.o test.out

test: test.out
	./test.out

Allocator.o: Allocator.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test.out: test.cpp AllocatorTester.o  Allocator.o InitException.o
	$(CC) $(CFLAGS) $^ -o $@

AllocatorTester.o: AllocatorTester.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

InitException.o: InitException.cpp
	$(CC) $(CFLAGS) -c $^ -o $@


clean:
	rm -rf *.o
	rm -rf *.out