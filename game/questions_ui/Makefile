.PHONY: all clean build debug tests run-tests
.SUFFIXES: .o .cpp .ttf .png

PROJECT = question_ui-app

CXX = g++
LINK = ld
STRIP = strip

CXXFLAGS = -MMD -MP -Wall -I../questions_core/ -std=c++20 -pedantic
LDFLAGS = -fPIC \
	  -lsfml-graphics \
	  -lsfml-window \
	  -lsfml-system \
	  -lm \
	  -L../questions_core/ \
	  -l:questions_core.a \
	  -ljsoncpp \

OBJS = \
question_window.o \
question_ui.o \
ui_exceptions.o \
font_arial.o \
scroll_bgrd.o \

DEPS = $(OBJS:%.o=%.d)

all: build | tests

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	$(CXX) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)

debug: CXXFLAGS += -g
debug: clean | compile
	$(CXX) $(OBJS) -o $(PROJECT) $(LDFLAGS)

tests: build
	make -C tests/

run-tests: tests
	make run -C tests/

clean:
	rm -f $(OBJS) $(DEPS)

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

.ttf.o:
	$(LINK) -r -b binary $< -o $@

.png.o:
	$(LINK) -r -b binary $< -o $@

-include $(DEPS)
