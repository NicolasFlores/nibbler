#!/bin/bash
mkdir -p ./lib
mkdir -p ./lib/irrKlang
curl -O https://www.soundjay.com/misc/fail-trombone-01.wav
curl -O http://www.ambiera.at/downloads/irrKlang-64bit-1.6.0.zip
mv irrKlang-64bit-1.6.0.zip ./lib/irrKlang/. && cd lib/irrKlang
unzip irrKlang-64bit-1.6.0.zip
rm irrKlang-64bit-1.6.0.zip
cd ../..
curl -O http://s1download-universal-soundbank.com/wav/14086.wav

#################

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

###############

ROOT_DIR=$(pwd)
mkdir -p ./lib
mkdir -p ./lib/SDL2
rm -Rf ./lib/SDL2
curl -O https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
tar -xvf SDL2-2.0.8.tar.gz -C ./lib/
rm -f SDL2-2.0.8.tar.gz
mkdir -p ./lib/SDL2-2.0.8/build
pushd ./lib/SDL2-2.0.8/build
../configure --prefix $ROOT_DIR/lib/SDL2
make -j6
make install
popd
rm -R ./lib/SDL2-2.0.8
echo "Now run:"
echo "export DYLD_LIBRARY_PATH=`pwd`/lib/SDL2/lib"
