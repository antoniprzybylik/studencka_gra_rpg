.PHONY: clean all run

all:
	g++ menu_tests.cpp ../menu.o \
		../font_arial.o \
		-o ui_tests \
		-I../ -lsfml-system \
		-lsfml-graphics -lsfml-window \

run:
	./menu_tests

clean:
	rm -f ./menu_tests
