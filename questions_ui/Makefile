.PHONY: all clean build debug
.SUFFIXES: .o .cpp

PROJECT = questions_ui

CXX = g++
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -I../classes/ -std=c++20
LDFLAGS = -fPIC

OBJS = \
question.o \
question_ui.o \
question_window.o \

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

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

-include $(DEPS)
