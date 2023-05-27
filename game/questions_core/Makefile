.PHONY: all clean build debug tests run-tests
.SUFFIXES: .o .cpp

TARGET = questions_core.a

CXX = g++
LINK = ld

CXXFLAGS = -MMD -MP -std=c++20 -Wall -pedantic

OBJS = \
question.o \
player.o \
enemy.o \

DEPS = $(OBJS:%.o=%.d)

all: build | tests

compile: $(OBJS)

build: CXXFLAGS += -O3
build: compile
	ar r $(TARGET) $(OBJS)
	ranlib $(TARGET)

debug: CXXFLAGS += -DGLIBCXX_DEBUG -g
debug: clean | compile
	ar r $(TARGET) $(OBJS)
	ranlib $(TARGET)

tests:
	make -C tests/

run-tests:
	make run -C tests/

clean:
	rm -f $(OBJS) $(DEPS)

%.o : %.cpp
	$(CXX) $< -o $@ -c $(CXXFLAGS)

-include $(DEPS)
