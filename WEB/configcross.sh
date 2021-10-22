#!/bin/bash

LUA_VERSION=5.3.4

PREFIX=$(pwd)/lualib
mkdir -p $PREFIX

cd ..
printf "Chose: \n$(ls *.ini)\n(ge.ini): "
read INI
if [ "X$INI" == "X" ]; then
   INI=ge.ini
fi
cd WEB

echo "Selecionado:[$INI]"

if [ ! -d emsdk ]; then
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   git pull
   # Download and install the latest SDK tools.
   ./emsdk install latest
   # Make the "latest" SDK "active" for the current user. (writes .emscripten file)
   ./emsdk activate latest
   cd ../
fi

cd emsdk
# Activate PATH and other environment variables in the current terminal
. ./emsdk_env.sh
echo source ./emsdk_env.sh
cd ../

if [ ! -f lua-${LUA_VERSION}.tar.gz ]; then
 wget  http://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz 
fi

if [ ! -d lua-${LUA_VERSION} ]; then
   tar xvf lua-${LUA_VERSION}.tar.gz
fi

if [ ! -d lualib ]; then
  mkdir lualib
fi

cd lua-${LUA_VERSION}
sed -i'' "s|^INSTALL_TOP=.*|INSTALL_TOP=$PREFIX|g" Makefile
make generic CC='emcc -s WASM=1' AR='emar rcu' RANLIB='emranlib'
#make generic CC='emcc -s WASM=1'
make install
cd ..

if [ -d ASSETS ] ; then
   rm -fr ASSETS 
fi

mkdir ASSETS
cd ..

tar cf - $(egrep -v "^#|^$" $INI | egrep ".*=.*\.png$|.*=.*\.ogg$|.*=.*\.ttf" | sed 's|legend.*=..||g' | sed 's|.*=||g') | tar xvf - -C WEB/ASSETS

cp $INI WEB/ASSETS/ge.ini
cp img/not_found.png WEB/ASSETS/img

# ref: https://github.com/emscripten-core/emscripten/issues/11985
