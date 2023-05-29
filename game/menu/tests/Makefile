.PHONY: clean all build run

all: build
build: menu_tests

run: build
	./menu_tests

clean:
	rm -f ./menu_tests ./menu_tests.o

menu_tests: menu_tests.o
	g++ menu_tests.o -o menu_tests \
		../menu.o ../font_arial.o \
		-lsfml-graphics -lsfml-window \
		-lsfml-system \

menu_tests.o: menu_tests.cpp
	g++ $< -o $@ -c -I../
