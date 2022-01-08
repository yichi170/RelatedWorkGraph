all: project

.PHONY: project test cpptest pybind clean autotest

project:
	make -C src/

cpptest: project
	make testcpp -C src/

pybind:
	make pybind -C src/

test: project
	make test -C test/

demo: project
	make test -C test/

interact: project
	make interact -C test/

clean:
	make clean -C src/
	make clean -C test/

autotest: clean
	make project && make test
