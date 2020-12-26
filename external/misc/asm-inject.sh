#!/bin/bash

if [ $1 == "NTSCU" ] ; then
    ARENALO="0x8033a0b0"
    MAIN_TRAMPOLINE="0x803737b4"
    RETURN_TO_MAIN="0x4BC92CA0"
    SET_WATER_DROP_EFFECT="0x801244a4"    
    DEBUG="0x8000b8a4"
elif [ $1 == "NTSCJ" ] ; then
    ARENALO="0x8033c54c"
    MAIN_TRAMPOLINE="0x80375c44"
    RETURN_TO_MAIN="0x4BC90810"
    SET_WATER_DROP_EFFECT="0x801244f0"
    DEBUG="0x8000b8a4"
elif [ $1 == "PAL" ]; then
    ARENALO="0x8033aeb0"
    MAIN_TRAMPOLINE="0x803745e4"
    RETURN_TO_MAIN="0x4bc91e70"
    SET_WATER_DROP_EFFECT="0x801246b0"
    DEBUG="0x8000b878"
EOF
else 
    echo "Invalid region: $1"
    exit 1
fi

echo "Compiling for $1"
sed "s/@arenaLo:/$ARENALO:/g" patch.asm > regional-patch.asm
sed -i "s/@mainTrampoline:/$MAIN_TRAMPOLINE:/g" regional-patch.asm
sed -i "s/@returnMn/$RETURN_TO_MAIN/g" regional-patch.asm
sed -i "s/@setWaterDropEffect:/$SET_WATER_DROP_EFFECT:/g" regional-patch.asm
sed -i "s/@debug:/$DEBUG:/" regional-patch.asm