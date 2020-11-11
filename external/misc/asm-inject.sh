#!/bin/bash

if [ $1 == "NTSCU" ] ; then
    cat <<EOF > patch.asm
0x8033a0b0:
; lis r3, 0x8050 ; set Arena low to 0x80507be0
; with inject at 0x80460000 gives us 0xA7BE0 bytes
u32 0x3c60804A
u32 0x38631FFF

; This will hook the main() function
0x80006454:
b apply_lib_hooks

; main_tampoline
; This is an unused section of the dol that we use to store the trampoline for the main function.
0x803737b4:
u32 0x9421fff0 ; stwu r1,-0x10(r1)  ; First instruction from original main()
u32 0x4BC92CA0 ; b main() + 4       ; branch to second instruction of main()

; Patch the setWaterDropEffect function to allow for custom tunic colors
0x801244a4:
u32 0x60000000
u32 0x60000000
u32 0x60000000

; Enable debug crash screen
0x8000b8a4:
u32 0x48000014
EOF
fi
