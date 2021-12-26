all: project

.PHONY: test clean autograde

project:
	make -C src/

test: project
	make test -C test/

cpptest: project
	make test -C src/

pybind:
	make pybind -C src/

clean:
	make clean -C src/
	make clean -C test/

autotest: clean
	make project && make test
