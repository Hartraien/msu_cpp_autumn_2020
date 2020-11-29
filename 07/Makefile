CC = g++

CFLAGS = -std=c++17 -g -Wall -O1

VPATH = ./src:./src/exc:./test

all: test.out

test: test.out
	./test.out

test_compile_error: test_compile_error.out
	./test_compile_error.out

test_compile_error.out: test_compile_error.cpp Formatter.o
	$(CC) $(CFLAGS) $^ -o $@

test.out: test.cpp Formatter.o FormatterTester.o
	$(CC) $(CFLAGS) $^ -o $@

FormatterTester.o: FormatterTester.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

Formatter.o: Formatter.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.out