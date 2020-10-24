CC = g++

CFLAGS = -std=c++17 -g -Wall

VPATH = ./src:./test

all: TokenParser.o test.out

test: test.out
	./test.out

TokenParser.o: TokenParser.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test.out: test.cpp TokenParserTester.o  TokenParser.o
	$(CC) $(CFLAGS) $^ -o $@

TokenParserTester.o: TokenParserTester.cpp
	$(CC) $(CFLAGS) -c $^ -o $@



clean:
	rm -rf *.o
	rm -rf *.out