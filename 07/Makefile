CC = g++
DEPDIR := .deps
.SUFFIXES += .d

CFLAGS = -std=c++17 -g -Wall -O1
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.td
POSTCOMPILE = mv -f $(DEPDIR)/$*.td $(DEPDIR)/$*.d && touch $(DEPDIR)/$@

objects = test.o VectorTester.o
deps = 

VPATH = ./src:./src/exc:./test:./.deps

all: test.out

test: test.out
	./test.out

test.out: $(objects)
	$(CC) $(CFLAGS) $^ -o $@


$(objects): %.o: %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) $< -c
	$(POSTCOMPILE)

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf $(DEPDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(objects:%.o=$(DEPDIR)/%.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))