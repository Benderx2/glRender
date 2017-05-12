#!/bin/sh
export CPPFLAGS="-I./include/ -std=c++11 -O3 -c -g"
export LDFLAGS="./lib/glRender.a -lSDL2 -lGL -lGLEW"
export CPP="g++"
export AR="ar"
export ARFLAGS="rvs"

COMPILE_START_TIME=$(date +%s.%N)

printf "Compiling started:\nDisplay module...\n"
$CPP $CPPFLAGS src/display.cpp -o display.o
printf "Skybox module...\n"
$CPP $CPPFLAGS src/skybox.cpp -o skybox.o
printf "Shader module...\n"
$CPP $CPPFLAGS src/shader.cpp -o shader.o
printf "Mesh module...\n"
$CPP $CPPFLAGS src/mesh.cpp -o mesh.o
printf "Texture module...\n"
$CPP $CPPFLAGS src/texture.cpp -o texture.o
printf "Object Loader module...\n"
$CPP $CPPFLAGS src/obj_loader.cpp -o obj_loader.o
printf "GameObject Module...\n"
$CPP $CPPFLAGS src/gameobject.cpp -o gameobject.o
printf "Primitives Module...\n"
$CPP $CPPFLAGS src/primitives.cpp -o primitives.o
printf "Scene Module...\n"
$CPP $CPPFLAGS src/scene.cpp -o scene.o
printf "Text module...\n"
$CPP $CPPFLAGS src/text.cpp -o text.o
printf "Public domain STB_IMAGE implementation...\n"
$CPP $CPPFLAGS src/stb_image.c -o stb_image.o
printf "Creating static library...\n"
$AR $ARFLAGS ./lib/glRender.a display.o shader.o mesh.o texture.o gameobject.o obj_loader.o stb_image.o scene.o text.o primitives.o skybox.o
printf "Compiling example...\n"
$CPP $CPPFLAGS ./examples/example01.cpp -o example01.o
$CPP example01.o -o ./bin/example01 $LDFLAGS

printf "Finished"
COMPILE_END_TIME=$(date +%s.%N)

TOTAL_TIME_TAKEN=$(echo "$COMPILE_END_TIME - $COMPILE_START_TIME" | bc)

printf "Compilation done!\nTime Taken: %s seconds.\n" $TOTAL_TIME_TAKEN
printf "Cleaning object files...\n"

rm *.o

printf "Cleaned. Run ./test.sh to test!\n"
