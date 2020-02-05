0x8033a0b0:
; lis r3, 0x8050 ; set Arena low to 0x80507be0
; with inject at 0x80460000 gives us 0xA7BE0 bytes
u32 0x3c608050

0x80006444:
bl game_loop
bl fapGm_Execute()
bl mDoAud_Execute()

0x8034f19c:
b read_controller