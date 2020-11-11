CC = g++

CFLAGS = -std=c++17 -g -Wall

VPATH = ./src:./test

all: test.out

test: test.out
	./test.out

test.out: test.cpp BigInteger.o BigIntegerTester.o
	$(CC) $(CFLAGS) $^ -o $@

BigIntegerTester.o: BigIntegerTester.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

BigInteger.o: BigInteger.cpp
	$(CC) $(CFLAGS) -c $^ -o $@



clean:
	rm -rf *.o
	rm -rf *.out