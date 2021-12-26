CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O3
SHRFLAG = -shared -fPIC
OSXFLAG = -undefined dynamic_lookup
PYBINC = -I../extern/pybind11/include
PYINC = `python3 -m pybind11 --includes` `python3-config --includes`
TESTPATH = ../test
OUTPUT = nodepy`python3-config --extension-suffix`

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
	OSXFLAGS += $(OSXFLAG)
endif

.PHONY: all clean test pybind

all: pybind

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

pybind: pybind.cpp system.o node.o
	$(CXX) $(CXXFLAGS) $(OSXFLAGS) $(SHRFLAG) $(PYBINC) $(PYINC) $^ -o $(TESTPATH)/$(OUTPUT)

test: test.o node.o system.o
	$(CXX) $(CXXFLAGS) $(OSXFLAGS) $^ -o $@

testcpp: test
	./test

clean:
	rm -f *.so *.o node test
	rm -rf *.dSYM/

# testpy: pybind
# 	python3 ../test/test.py
