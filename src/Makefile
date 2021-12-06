CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O3

.PHONY: all clean test

all: target

target: test.cpp node.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test: target
	./target

clean:
	rm -f *.o target
	rm -rf *.dSYM/