CC = g++

CFLAGS = -std=c++17 -g -Wall -O1

VPATH = ./src:./test

all: test.out

test: test.out
	./test.out

test_compile_error: test_compile_error.out
	./test_compile_error.out

test_compile_error.out: test_compile_error.cpp Serializer.o Deserializer.o
	$(CC) $(CFLAGS) $^ -o $@

test.out: test.cpp Serializer.o Deserializer.o SerializerTester.o
	$(CC) $(CFLAGS) $^ -o $@

SerializerTester.o: SerializerTester.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

Serializer.o: Serializer.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

Deserializer.o: Deserializer.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.out