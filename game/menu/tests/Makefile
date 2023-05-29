.PHONY: clean all run

all: menu_tests.o
	g++ menu_tests.o -o menu_tests \
		../menu.o ../font_arial.o \
		-lsfml-graphics -lsfml-window \
		-lsfml-system \

run:
	./menu_tests

clean:
	rm -f ./menu_tests ./menu_tests.o

menu_tests.o: menu_tests.cpp
	g++ $< -o $@ -c -I../
