#!/bin/bash

if [ $1 == "GCN_NTSCU" ] ; then
    SRC_ISO="gz2e01.iso"
    SRC_MAP="map/Final/Release/frameworkF.map"
    BLD_ISO="build/tpgz.iso"
    BLD_MAP="build/GZ2E01.map"
    LINK_BASE="0x8046_0000"
elif [ $1 == "GCN_NTSCJ" ] ; then
    SRC_ISO="gz2e01.iso"
    SRC_MAP="map/Final/Release/frameworkF.map"
    BLD_ISO="build/tpgz.iso"
    BLD_MAP="build/GZ2E01.map"
    LINK_BASE="0x8046_0000"
elif [ $1 == "GCN_PAL" ]; then
    SRC_ISO="gz2e01.iso"
    SRC_MAP="map/Final/Release/frameworkF.map"
    BLD_ISO="build/tpgz.iso"
    BLD_MAP="build/GZ2E01.map"
    LINK_BASE="0x8046_0000"
elif [ $1 == "WII_NTSCU_10" ]; then
    SRC_ISO="rzde01.iso"
    SRC_MAP="map/Rfinal/Release/RframeworkF.map"
    BLD_ISO="build/tpgzw.iso"
    BLD_MAP="build/RZDE01.map"
    LINK_BASE="0x8056_0000"
else 
    echo "Invalid region: $1"
    exit 1
fi

echo "Compiling for $1"
sed "s=@srcIso=$SRC_ISO=g" RomHack-template.toml > RomHack.toml
sed -i "s=@srcMap=$SRC_MAP=g" RomHack.toml
sed -i "s=@bldIso=$BLD_ISO=g" RomHack.toml
sed -i "s=@bldMap=$BLD_MAP=g" RomHack.toml
sed -i "s=@linkBase=$LINK_BASE=g" RomHack.toml