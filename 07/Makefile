CC = g++
DEPDIR := .deps
SUFFIXES += .d

CFLAGS = -std=c++17 -g -Wall -O1
DEPFLAGS = -MT $@ -MM -MP -MF $(DEPDIR)/$*.td
POSTCOMPILE = mv -f $(DEPDIR)/$*.td $(DEPDIR)/$*.d && touch $@

VPATH = ./src:./src/exc:./test

all: test.out

test: test.out
	./test.out

test.out: test.o VectorTester.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.cpp test.d | $(DEPDIR)
	$(CC) $(CFLAGS) $< -c -o $@

test.d: test.cpp | $(DEPDIR)
	$(CC) $(DEPFLAGS) $<
	$(POSTCOMPILE)

VectorTester.o: VectorTester.cpp VectorTester.d | $(DEPDIR)
	$(CC) $(CFLAGS) $< -c -o $@

VectorTester.d: VectorTester.cpp | $(DEPDIR)
	$(CC) $(DEPFLAGS) $<
	$(POSTCOMPILE)

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf $(DEPDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))