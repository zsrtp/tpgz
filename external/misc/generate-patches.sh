#!/bin/bash
version=$1

if [ -z "$version" ]
then
    exit 1
fi

make clean

export PLATFORM="GCN"
export REGION="NTSCU"
make
romhack build --raw --patch
mv ./build/tpgz.patch ./$version-gcn-ntscu.patch
make clean
export REGION="NTSCJ"
make
romhack build --raw --patch
mv ./build/tpgz.patch ./$version-gcn-ntscj.patch
make clean
export REGION="PAL"
make
romhack build --raw --patch
mv ./build/tpgz.patch ./$version-gcn-pal.patch
make clean
export PLATFORM="WII"
export REGION="NTSCU_10"
make
romhack build --raw --patch
mv ./build/tpgzw.patch ./$version-wii-ntscu-10.patch
make clean
export PLATFORM="WII"
export REGION="PAL"
make
romhack build --raw --patch
mv ./build/tpgzw.patch ./$version-wii-pal.patch
make clean