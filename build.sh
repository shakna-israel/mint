#!/bin/sh

rm -rf build
mkdir build
if [ "$1" != 'release' ]
then
  g++ -std=c++14 src/main.cpp -o build/mint.debug
else
  g++ -std=c++14 src/main.cpp -o build/mint.debug > /dev/null
fi

if [ "$1" = 'release' ]
then
  g++ -std=c++14 -static -Os -s -fno-exceptions -flto -fno-rtti -fno-stack-protector -ffunction-sections -fdata-sections -fno-math-errno -fmerge-all-constants -fno-ident -ffast-math -Wl,--gc-sections src/main.cpp -o build/mint
  upx --brute build/mint
  ls -lah build/mint
else
  g++ -std=c++14 -static -Os -s -fno-exceptions -flto -fno-rtti -fno-stack-protector -ffunction-sections -fdata-sections -fno-math-errno -fmerge-all-constants -fno-ident -ffast-math -Wl,--gc-sections src/main.cpp -o build/mint > /dev/null
fi

