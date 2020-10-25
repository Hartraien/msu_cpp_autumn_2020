CC = g++

CFLAGS = -std=c++17 -g -Wall

VPATH = ./src:./test

all: MatrixTester.o test.out

test: test.out
	./test.out

test.out: test.cpp Matrix.o  MatrixRow.o MatrixTester.o
	$(CC) $(CFLAGS) $^ -o $@

MatrixTester.o: MatrixTester.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

Matrix.o: Matrix.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

MatrixRow.o: MatrixRow.cpp
	$(CC) $(CFLAGS) -c $^ -o $@



clean:
	rm -rf *.o
	rm -rf *.out