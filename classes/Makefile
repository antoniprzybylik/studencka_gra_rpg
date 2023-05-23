.PHONY: all clean build debug
.SUFFIXES: .o .cpp

PROJECT = classes.o

CXX = g++
LINK = ld
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -std=c++20
LDFLAGS = -relocatable

OBJS = \
enemy.o \
player.o \
question.o \

DEPS = $(OBJS:%.o=%.d)

all: build

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)

debug: CXXFLAGS += -g
debug: clean | compile
	$(LINK) $(OBJS) -o $(PROJECT) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(DEPS)

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

-include $(DEPS)
