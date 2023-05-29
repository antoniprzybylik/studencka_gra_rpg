.PHONY: all clean build debug
.SUFFIXES: .o .cpp .ttf .png

TARGET1 = demo
TARGET2 = question_ui.a

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
question_ui.o \
ui_exceptions.o \
font_arial.o \
scroll_bgrd.o \

DEPS = $(OBJS:%.o=%.d)

all: build

compile: $(OBJS) demo_main.o

build: CXXFLAGS += -O3
build: compile
	$(CXX) $(OBJS) demo_main.o -o $(TARGET1) $(LDFLAGS)
	$(STRIP) $(TARGET1)

	ar r $(TARGET2) $(OBJS)
	ranlib $(TARGET2)

debug: CXXFLAGS += -g
debug: clean | compile
	$(CXX) $(OBJS) demo_main.o -o $(TARGET1) $(LDFLAGS)

	ar r $(TARGET2) $(OBJS)
	ranlib $(TARGET2)

clean:
	rm -f $(OBJS) demo_main.o $(DEPS) demo_main.d

.cpp.o:
	$(CXX) $< -o $@ -c $(CXXFLAGS)

.ttf.o:
	$(LINK) -r -b binary $< -o $@

.png.o:
	$(LINK) -r -b binary $< -o $@

-include $(DEPS)
-include demo_main.d
