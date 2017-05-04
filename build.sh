#!/bin/sh
export CPPFLAGS="-I./include/ -std=c++11 -O3 -c"
export LDFLAGS="-lSDL2 -lGL -lGLEW"
export CPP="g++"

COMPILE_START_TIME=$(date +%s.%N)

printf "Compiling started:\nDisplay module...\n"
$CPP $CPPFLAGS display.cpp -o display.o
printf "Main module...\n"
$CPP $CPPFLAGS main.cpp -o main.o
printf "Shader module...\n"
$CPP $CPPFLAGS shader.cpp -o shader.o
printf "Mesh module...\n"
$CPP $CPPFLAGS mesh.cpp -o mesh.o
printf "Texture module...\n"
$CPP $CPPFLAGS texture.cpp -o texture.o
printf "Object Loader module...\n"
$CPP $CPPFLAGS obj_loader.cpp -o obj_loader.o
printf "GameObject Module...\n"
$CPP $CPPFLAGS gameobject.cpp -o gameobject.o
printf "Scene Module...\n"
$CPP $CPPFLAGS scene.cpp -o scene.o
printf "Text module...\n"
$CPP $CPPFLAGS text.cpp -o text.o
printf "Public domain STB_IMAGE implementation...\n"
$CPP $CPPFLAGS stb_image.c -o stb_image.o
printf "Linking to form executable...\n"
$CPP main.o display.o shader.o mesh.o texture.o gameobject.o obj_loader.o stb_image.o scene.o text.o -o engine $LDFLAGS

COMPILE_END_TIME=$(date +%s.%N)

TOTAL_TIME_TAKEN=$(echo "$COMPILE_END_TIME - $COMPILE_START_TIME" | bc)

printf "Compilation done!\nTime Taken: %s seconds.\n" $TOTAL_TIME_TAKEN
printf "Cleaning object files...\n"

rm *.o

printf "Cleaned. Run ./engine to test!\n"
