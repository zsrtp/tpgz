SECTIONS {
    .ctors : { *(.ctors .ctors.*) }
    .dtors : { *(.dtors .dtors.*) }
    .init : { *(.init .init.*) }
    .text : { *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data* .data.*) }
    .bss : { *(.bss .bss.*) }
}