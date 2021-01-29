#!/bin/bash

if [ $1 == "GCN_NTSCU" ] ; then
    ARENALO="0x8033a0b0"
    ARENALO_VAL="0x3c60804A"
    MAIN="0x80006454"
    MAIN_TRAMPOLINE="0x803737b4"
    FIRST_INSTRUCTION="0x9421fff0"
    RETURN_TO_MAIN="0x4BC92CA0"
    SET_WATER_DROP_EFFECT1="0x801244a4"
    SET_WATER_DROP_EFFECT2="0x801244a8"
    SET_WATER_DROP_EFFECT3="0x801244ac"
    SET_SWORD_UP_COLOR_EFFECT="0x801244a4"
    DEBUG="0x8000b8a4"
    DEBUG_INSTRUCTION="0x48000014"
elif [ $1 == "GCN_NTSCJ" ] ; then
    ARENALO="0x8033c54c"
    ARENALO_VAL="0x3c60804A"
    MAIN="0x80006454"
    MAIN_TRAMPOLINE="0x80375c44"
    FIRST_INSTRUCTION="0x9421fff0"
    RETURN_TO_MAIN="0x4BC90810"
    SET_WATER_DROP_EFFECT1="0x801244f0"
    SET_WATER_DROP_EFFECT2="0x801244f4"
    SET_WATER_DROP_EFFECT3="0x801244f8"
    SET_SWORD_UP_COLOR_EFFECT="0x801244f0"
    DEBUG="0x8000b8a4"
    DEBUG_INSTRUCTION="0x48000014"
elif [ $1 == "GCN_PAL" ]; then
    ARENALO="0x8033aeb0"
    ARENALO_VAL="0x3c60804A"
    MAIN="0x80006454"
    MAIN_TRAMPOLINE="0x803745e4"
    FIRST_INSTRUCTION="0x9421fff0"
    RETURN_TO_MAIN="0x4bc91e70"
    SET_WATER_DROP_EFFECT1="0x801246b0"
    SET_WATER_DROP_EFFECT2="0x801246b4"
    SET_WATER_DROP_EFFECT3="0x801246b8"
    SET_SWORD_UP_COLOR_EFFECT="0x801246b0"
    DEBUG="0x8000b878"
    DEBUG_INSTRUCTION="0x48000014"
elif [ $1 == "WII_NTSCU_10" ]; then
    ARENALO="0x803449dc"
    ARENALO_VAL="0x3c608058"
    MAIN="0x80008cec"
    MAIN_TRAMPOLINE="0x803ce3dc"
    FIRST_INSTRUCTION="0x542b06fe"
    RETURN_TO_MAIN="0x4bc3a910"
    SET_WATER_DROP_EFFECT1="0x8011759c"
    SET_WATER_DROP_EFFECT2="0x801175ac"
    SET_WATER_DROP_EFFECT3="0x801175bc"
    SET_SWORD_UP_COLOR_EFFECT="0x801176B0"
    DEBUG="0x80011f90"
    DEBUG_INSTRUCTION="0x48000190"
else 
    echo "Invalid region: $1"
    exit 1
fi

echo "Compiling for $1"
sed "s/@arenaLo:/$ARENALO:/g" patch.asm > regional-patch.asm
sed -i "s/@arenaLoVal/$ARENALO_VAL/g" regional-patch.asm
sed -i "s/@main:/$MAIN:/g" regional-patch.asm
sed -i "s/@mainTrampoline:/$MAIN_TRAMPOLINE:/g" regional-patch.asm
sed -i "s/@firstInstruction/$FIRST_INSTRUCTION/g" regional-patch.asm
sed -i "s/@returnMn/$RETURN_TO_MAIN/g" regional-patch.asm
sed -i "s/@setWaterDropEffect1:/$SET_WATER_DROP_EFFECT1:/g" regional-patch.asm
sed -i "s/@setWaterDropEffect2:/$SET_WATER_DROP_EFFECT2:/g" regional-patch.asm
sed -i "s/@setWaterDropEffect3:/$SET_WATER_DROP_EFFECT3:/g" regional-patch.asm
sed -i "s/@debug:/$DEBUG:/" regional-patch.asm
sed -i "s/@debugInstruction/$DEBUG_INSTRUCTION/" regional-patch.asm