.PHONY: clean all build run

all: build
build: ui_tests

run: build
	./ui_tests

clean:
	rm -f ui_tests ui_tests.o

ui_tests: ui_tests.o
	g++ ui_tests.o -o ui_tests \
		../question_ui.o \
		../font_arial.o ../scroll_bgrd.o \
		../ui_exceptions.o \
		-L../../questions_core/ \
		-l:questions_core.a \
		-ljsoncpp -lsfml-system \
		-lsfml-graphics -lsfml-window \

ui_tests.o: ui_tests.cpp
	g++ ui_tests.cpp -o ui_tests.o -c \
		-I../ -I../../questions_core/ \
