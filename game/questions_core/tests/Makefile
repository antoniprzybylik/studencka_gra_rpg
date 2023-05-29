.PHONY: clean all build run

all: build
build: classes_tests

run: build
	./classes_tests

clean:
	rm -f classes_tests classes_tests.o

classes_tests: classes_tests.o
	g++ classes_tests.o -o classes_tests \
		-L../ -l:questions_core.a \
		-ljsoncpp \

classes_tests.o:
	g++ classes_tests.cpp -o classes_tests.o \
		-I../ -c \
