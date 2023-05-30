.PHONY: all clean build debug tests run-tests
.SUFFIXES: .o .cpp

PROJECT = game

CXX = g++
LINK = g++
STRIP = strip

CXXFLAGS = -MMD -MP -Wall \
	   -I../engine/ -I../questions_core/ \
	   -I../questions_ui \
	   -std=c++20 \

LDFLAGS = -fPIC -L../engine/ -lengine \
	  -L../questions_core/ -l:questions_core.a \
	  -L../questions_ui/ -l:question_ui.a \
	  -lsfml-graphics \
	  -lsfml-window \
	  -lsfml-system \
	  -lm \
	  -ljsoncpp \

OBJS = \
main.o \
game.o \
tile_sprite.o \
player_sprite.o \
boss_sprite.o \
label_sprite.o \
map.o \
map_generator.o \
tile_data.o \

DEPS = $(OBJS:%.o=%.d)

all: build | tests

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)

debug: CXXFLAGS += -g
debug: clean | compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)

tests: build
	make -C tests/

run-tests: tests
	make run -C tests/

clean:
	rm -f $(OBJS) $(DEPS)

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

-include $(DEPS)
