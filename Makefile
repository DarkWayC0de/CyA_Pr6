CC=g++
CXXFLAGS=-g -std=c++14

OBJ=Estado.o DFA.o main.o

all: DFA
Estado.o: Estado.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)
DFA.O: DFA.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)
main.o: main.cpp DFA.h Estado.h
	$(CC) -c -o $@ $< $(CXXFLAGS)

DFA: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) -lm

.PHONY: clean
clean:
	rm -f *.o *~
