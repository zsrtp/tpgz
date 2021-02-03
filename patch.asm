; Resize ArenaLo so the hack can be inserted without the game overwriting it
@arenaLo:
u32 @arenaLoVal
u32 0x38637FFF

; This will hook the main() function
@main:
b apply_lib_hooks

; This is an unused section of the dol that we use to store the trampoline for the main function.
@mainTrampoline:
u32 @firstInstruction ; stwu r1,-0x10(r1)  ; First instruction from original main()
u32 @returnMn ; b main() + 4       ; branch to second instruction of main()

; Patch the setWaterDropEffect function to allow for custom tunic colors
@setWaterDropEffect1:
u32 0x60000000
@setWaterDropEffect2:
u32 0x60000000
@setWaterDropEffect3:
u32 0x60000000

; Temporary fix for a save loader bug
; @setWaterDropColor:
; u32 0x60000000

; Enable debug crash screen
@debug:
u32 @debugInstruction