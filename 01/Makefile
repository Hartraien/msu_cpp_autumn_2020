CC = g++

CFLAGS = -g -Wall

VPATH = ./src:./test

all: Allocator.o test.out

test: test.out
	./test.out

Allocator.o: Allocator.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test.out: test.cpp AllocatorTester.o AllocatorTester.hpp
	$(CC) $(CFLAGS) $< -o $@

AllocatorTester.o: AllocatorTester.cpp Allocator.o AllocatorTester.hpp Allocator.hpp
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf ./build/*