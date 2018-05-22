#!/bin/bash
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
