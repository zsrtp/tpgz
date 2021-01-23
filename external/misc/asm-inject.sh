#!/bin/bash

if [ $1 == "NTSCU" ] ; then
    ARENALO="0x8033a0b0"
    ARENALO_VAL="0x3C60804D"
    MAIN_TRAMPOLINE="0x803737b4"
    RETURN_TO_MAIN="0x4BC92CA0"
    SET_WATER_DROP_EFFECT="0x801244a4"    
    SET_WATER_DROP_COLOR="0x800CCE08"
    DEBUG="0x8000b8a4"
elif [ $1 == "NTSCJ" ] ; then
    ARENALO="0x8033c54c"
    ARENALO_VAL="0x3C60804B"
    MAIN_TRAMPOLINE="0x80375c44"
    RETURN_TO_MAIN="0x4BC90810"
    SET_WATER_DROP_EFFECT="0x801244f0"
    SET_WATER_DROP_COLOR="0x800CCDE0"
    DEBUG="0x8000b8a4"
elif [ $1 == "PAL" ]; then
    ARENALO="0x8033aeb0"
    ARENALO_VAL="0x3C60804B"
    MAIN_TRAMPOLINE="0x803745e4"
    RETURN_TO_MAIN="0x4bc91e70"
    SET_WATER_DROP_EFFECT="0x801246b0"
    SET_WATER_DROP_COLOR="0x800CCFB4"
    DEBUG="0x8000b878"
else 
    echo "Invalid region: $1"
    exit 1
fi

echo "Compiling for $1"
sed "s/@arenaLo:/$ARENALO:/g" patch.asm > regional-patch.asm
sed -i "s/@arenaLoVal/$ARENALO_VAL/g" regional-patch.asm
sed -i "s/@mainTrampoline:/$MAIN_TRAMPOLINE:/g" regional-patch.asm
sed -i "s/@returnMn/$RETURN_TO_MAIN/g" regional-patch.asm
sed -i "s/@setWaterDropEffect:/$SET_WATER_DROP_EFFECT:/g" regional-patch.asm
sed -i "s/@setWaterDropColor:/$SET_WATER_DROP_COLOR:/g" regional-patch.asm
sed -i "s/@debug:/$DEBUG:/" regional-patch.asm