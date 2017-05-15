#!/bin/sh
export CPP="g++"
export CPPFLAGS="-I./include/ -std=c++11 -O3 -c -g"
export LDFLAGS="./lib/glRender.a -lSDL2 -lGL -lGLEW"

# 3D Example
$CPP $CPPFLAGS ./examples/example3d.cpp -o example3d.o
$CPP example3d.o -o ./bin/example3d $LDFLAGS

# 2D exempel
$CPP $CPPFLAGS ./examples/example2d.cpp -o example2d.o
$CPP example2d.o -o ./bin/example2d $LDFLAGS

rm *.o
