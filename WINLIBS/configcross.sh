#!/bin/bash

SDL2_VER=2.0.16
SDL2_TTF_VER=2.0.15
SDL2_IMAGE_VER=2.0.5
SDL2_MIXER_VER=2.0.4
JIT_VERSION=2.0.5

   sudo apt -y install unzip \
       binutils-mingw-w64-i686 \
       binutils-mingw-w64-x86-64 \
       g++-mingw-w64 \
       g++-mingw-w64-i686 \
       g++-mingw-w64-x86-64 \
       gcc-mingw-w64 \
       gcc-mingw-w64-base \
       gcc-mingw-w64-i686 \
       gcc-mingw-w64-x86-64 \
       libconfig++9v5 \
       mingw-w64 \
       mingw-w64-common \
       mingw-w64-i686-dev \
       mingw-w64-tools \
   mingw-w64-x86-64-dev
   
   # Download SDL2
   if [ ! -f SDL2-devel-${SDL2_VER}-mingw.tar.gz ]; then
      wget https://www.libsdl.org/release/SDL2-devel-${SDL2_VER}-mingw.tar.gz
      tar xvf SDL2-devel-${SDL2_VER}-mingw.tar.gz
   fi
   if [ ! -f SDL2-${SDL2_VER}-win32-x64.zip ]; then
      wget https://www.libsdl.org/release/SDL2-${SDL2_VER}-win32-x64.zip
      unzip -o  SDL2-${SDL2_VER}-win32-x64.zip
   fi
   
   # Download SDL2-ttf
   if [ ! -f SDL2_ttf-devel-${SDL2_TTF_VER}-mingw.tar.gz ]; then
      wget https://libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-${SDL2_TTF_VER}-mingw.tar.gz
      tar xvf SDL2_ttf-devel-${SDL2_TTF_VER}-mingw.tar.gz
   fi
   if [ ! -f SDL2_ttf-${SDL2_TTF_VER}-win32-x64.zip ]; then
     wget https://libsdl.org/projects/SDL_ttf/release/SDL2_ttf-${SDL2_TTF_VER}-win32-x64.zip
     unzip -o SDL2_ttf-${SDL2_TTF_VER}-win32-x64.zip
   fi
   
   # Download SDL2_images
   if [ ! -f SDL2_image-devel-${SDL2_IMAGE_VER}-mingw.tar.gz ]; then
     wget https://libsdl.org/projects/SDL_image/release/SDL2_image-devel-${SDL2_IMAGE_VER}-mingw.tar.gz
     tar xvf SDL2_image-devel-${SDL2_IMAGE_VER}-mingw.tar.gz
   fi
   if [ ! -f SDL2_image-${SDL2_IMAGE_VER}-win32-x64.zip ]; then
     wget https://libsdl.org/projects/SDL_image/release/SDL2_image-${SDL2_IMAGE_VER}-win32-x64.zip
     unzip -o SDL2_image-${SDL2_IMAGE_VER}-win32-x64.zip
   fi
   
   # Download SDL2_mixer
   if [ ! -f SDL2_mixer-devel-${SDL2_MIXER_VER}-mingw.tar.gz ]; then
     wget https://libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-${SDL2_MIXER_VER}-mingw.tar.gz
     tar xvf SDL2_mixer-devel-${SDL2_MIXER_VER}-mingw.tar.gz
   fi
   if [ ! -f SDL2_mixer-${SDL2_MIXER_VER}-win32-x64.zip ]; then
     wget https://libsdl.org/projects/SDL_mixer/release/SDL2_mixer-${SDL2_MIXER_VER}-win32-x64.zip
     unzip -o SDL2_mixer-${SDL2_MIXER_VER}-win32-x64.zip
   fi

# Download precompiled luajit package 
# if [ ! -f mingw-w64-x86_64-luajit-2.1.0_beta3-2-any.pkg.tar.zst ]; then
#  wget https://mirror.msys2.org/mingw/mingw64/mingw-w64-x86_64-luajit-2.1.0_beta3-2-any.pkg.tar.zst
#  sudo apt -y install zstd
#  cat mingw-w64-x86_64-luajit-2.1.0_beta3-2-any.pkg.tar.zst | zstd -d | tar -xvf -
# fi

# Downloas and compile LuaJIT
if [ ! -f LuaJIT-${JIT_VERSION}.tar.gz ]; then
  wget http://luajit.org/download/LuaJIT-${JIT_VERSION}.tar.gz
fi

if [ ! -d LuaJIT-${JIT_VERSION} ]; then
   tar xvf LuaJIT-${JIT_VERSION}.tar.gz
fi

cd LuaJIT-${JIT_VERSION}

make HOST_CC="gcc " CROSS=x86_64-w64-mingw32- TARGET_SYS=Windows

cp -v src/lua*.dll ../

cd ../
zip -r windlls.zip *.dll

mkdir -p  mingw64/include/host mingw64/include/dynasm
cp LuaJIT-${JIT_VERSION}/src/*.h mingw64/include
cp LuaJIT-${JIT_VERSION}/dynasm/*.h mingw64/include/dynasm
cp LuaJIT-${JIT_VERSION}/src/host/*.h mingw64/include/host

cp windlls.zip ../
cd ../
unzip -o windlls.zip
