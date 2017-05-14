#!/bin/sh
export CPP="g++"
export CPPFLAGS="-I./include/ -std=c++11 -O3 -c -g"
export LDFLAGS="./lib/glRender.a -lSDL2 -lGL -lGLEW"
$CPP $CPPFLAGS ./examples/example01.cpp -o example01.o
$CPP example01.o -o ./bin/example01 $LDFLAGS

rm *.o
