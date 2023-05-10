.PHONY: all clean build debug
.SUFFIXES: .o .cpp

PROJECT = menu-app

CXX = g++
LINK = ld
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -std=c++20 -pedantic
LDFLAGS = -fPIC  \
	  -lsfml-graphics \
	  -lsfml-window \
	  -lsfml-system \

OBJS = \
main.o \
menu.o \
font_arial.o \

DEPS = $(OBJS:%.o=%.d)

all: build

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	$(CXX) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)

debug: CXXFLAGS += -g
debug: clean | compile
	$(CXX) $(OBJS) -o $(PROJECT) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(DEPS)

%.o : %.cpp
	$(CXX) $< -o $@ -c $(CXXFLAGS)

%.o : %.ttf
	$(LINK) -r -b binary $< -o $@

-include $(DEPS)
