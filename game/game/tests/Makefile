.PHONY: clean build all run

all: build
build: game-tests

game-tests: game_tests.o
	g++ game_tests.o -o game_tests \
		../map.o ../map_generator.o -ljsoncpp \

game_tests.o: game_tests.cpp
	g++ game_tests.cpp -o game_tests.o \
		-c -I../ \

run: build
	./game_tests

clean:
	rm -f game_tests game_tests.o
