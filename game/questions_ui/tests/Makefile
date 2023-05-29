.PHONY: clean all run

all:
	g++ ui_tests.cpp ../question_ui.o \
		../font_arial.o ../scroll_bgrd.o \
		../ui_exceptions.o \
		-o ui_tests \
		-I../ -I../../questions_core/ \
		-L../../questions_core/ \
		-l:questions_core.a \
		-ljsoncpp -lsfml-system \
		-lsfml-graphics -lsfml-window \

run:
	./ui_tests

clean:
	rm -f ui_tests
