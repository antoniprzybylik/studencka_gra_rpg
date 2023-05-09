#!/bin/sh

g++ -c main.cpp menu.cpp
g++ main.o menu.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app