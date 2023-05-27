.PHONY: clean all run

all:
	g++ classes_tests.cpp -o classes_tests -I../ -L../ -l:questions_core.a

run:
	./classes_tests

clean:
	rm -f classes_tests
