#!/bin/bash
rm -Rf ./lib/imgui
git clone https://github.com/ocornut/imgui.git ./lib/imgui

pushd ./lib/imgui

g++ -fPIC -c `../SDL2/bin/sdl2-config --cflags` -I./ -I./examples/libs/gl3w ./examples/sdl_opengl3_example/imgui_impl_sdl_gl3.cpp
g++ -fPIC -c `../SDL2/bin/sdl2-config --cflags` -I./ -I./examples/libs/gl3w ./examples/libs/gl3w/GL/gl3w.c
g++ -fPIC -c ./imgui.cpp
g++ -fPIC -c ./imgui_draw.cpp
g++ -fPIC -c ./imgui_demo.cpp
mkdir -p ./include
mkdir -p ./bin
ar -rcs ./bin/imgui.a imgui.o imgui_draw.o imgui_demo.o imgui_impl_sdl_gl3.o gl3w.o
cp imgui.h imconfig.h imgui_internal.h stb_rect_pack.h stb_textedit.h stb_truetype.h ./examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h ./include
cp -R ./examples/libs/gl3w/GL ./include

popd

rm -Rf ./lib/glm
git clone https://github.com/g-truc/glm.git ./lib/glm

echo "Done"
