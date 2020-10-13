CC = g++

CFLAGS = -g -Wall

VPATH = ./src:./test

BUILDDIR = build

all: $(BUILDDIR)/Allocator.o $(BUILDDIR)/test.out

test: test.out
	./test.out

$(BUILDDIR)/Allocator.o: Allocator.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/test.out: test.cpp AllocatorTester.o
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/AllocatorTester.o: AllocatorTester.cpp Allocator.o
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf *.out
	rm -rf *.o