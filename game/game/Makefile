.PHONY: all clean build debug
.SUFFIXES: .o .cpp

PROJECT = game

CXX = g++
LINK = g++
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -I../engine/ -std=c++20
LDFLAGS = -fPIC -L../engine/ -lengine \
	  -lsfml-graphics \
	  -lsfml-window \
	  -lsfml-system \
	  -lm \

OBJS = \
main.o \
game.o \
tile_sprite.o \
player_sprite.o \
label_sprite.o \
map.o \
map_generator.o \
tile_data.o \

DEPS = $(OBJS:%.o=%.d)

all: build

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)

debug: CXXFLAGS += -g
debug: clean | compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(DEPS)

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

-include $(DEPS)
