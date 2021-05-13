#!/bin/bash
export GZ_VERSION=$1

if [ -z $GZ_VERSION ]
then
    echo "You need to specify a version. Ex: generate-patches.sh 1.0"
    exit 1
fi

make clean

# This can be optimized but too lazy atm
export PLATFORM="GCN"
export REGION="NTSCU"
make
romhack build --raw --patch
mv ./build/tpgz.patch ./$GZ_VERSION-gcn-ntscu.patch
make clean
export REGION="NTSCJ"
make
romhack build --raw --patch
mv ./build/tpgz.patch ./$GZ_VERSION-gcn-ntscj.patch
make clean
export REGION="PAL"
make
romhack build --raw --patch
mv ./build/tpgz.patch ./$GZ_VERSION-gcn-pal.patch
make clean
export PLATFORM="WII"
export REGION="NTSCU_10"
make
romhack build --raw --patch
mv ./build/tpgzw.patch ./$GZ_VERSION-wii-ntscu-10.patch
make clean
export PLATFORM="WII"
export REGION="PAL"
make
romhack build --raw --patch
mv ./build/tpgzw.patch ./$GZ_VERSION-wii-pal.patch
make clean