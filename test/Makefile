.PHONY: all clean test

all: test

test: # test node system with Networkx
	python3 test.py

demo: # connect node system with paperpy (Networkx)
	python3 demo.py

interact: # use dash_cytoscape
	python3 intermediate.py rel.txt pos.txt info.json
	python3 interact.py rel.txt pos.txt info.json

clean:
	$(RM) *.so
	$(RM) -r *.dSYM/
