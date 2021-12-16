CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O3
SHRFLAG = -shared -fPIC
OSXFLAG = -undefined dynamic_lookup
PYBINC = -I../extern/pybind11/include
PYINC = `python3 -m pybind11 --includes` `python3-config --includes`
OUTPUT = _graph`python3-config --extension-suffix`


.PHONY: all clean test

all: target

target: test.cpp node.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

pybind: pybind.cpp
	$(CXX) $(CXXFLAGS) $(SHRFLAG) $(OSXFLAG) $(PYBINC) $(PYINC) $< -o $(OUTPUT)

test: target
	./target

clean:
	rm -f *.o target
	rm -rf *.dSYM/