.PHONY: all clean build debug
.SUFFIXES: .o .cpp .ttf

PROJECT = question_ui-app

CXX = g++
LINK = ld
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -I../classes_fromui/ -std=c++20 -pedantic
LDFLAGS = -fPIC \
	  -lsfml-graphics \
	  -lsfml-window \
	  -lsfml-system \
	  -lm \
	  -L../classes_fromui/ \
	  -l:classes_fromui.a \

OBJS = \
question_window.o \
question_ui.o \
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

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

.ttf.o:
	$(LINK) -r -b binary $< -o $@

-include $(DEPS)
