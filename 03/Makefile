CC = g++

CFLAGS = -std=c++17 -g -Wall

VPATH = ./src:./test

all: TokenParser.o test.out

test: test.out
	./test.out

TokenParser.o: TokenParser.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test.out: test.cpp Matrix.o  MatrixRow.o MatrixTester.o
	$(CC) $(CFLAGS) $^ -o $@

MatrixTester.o: MatrixTester.cpp Matrix.o MatrixRow.out
	$(CC) $(CFLAGS) -c $^ -o $@

Matrix.o: Matrix.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

MatrixRow.o: MatrixRow.cpp
	$(CC) $(CFLAGS) -c $^ -o $@



clean:
	rm -rf *.o
	rm -rf *.out