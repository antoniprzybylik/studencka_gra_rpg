.PHONY: all clean build debug
.SUFFIXES: .o .cpp

PROJECT = menu-app

CXX = g++
LINK = g++
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -std=c++20 -pedantic
LDFLAGS = -fPIC  \
	  -lsfml-graphics \
	  -lsfml-window \
	  -lsfml-system \

OBJS = \
main.o \
menu.o \

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
