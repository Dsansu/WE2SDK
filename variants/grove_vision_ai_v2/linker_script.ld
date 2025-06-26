/*
 * Himax WE2 Linker Script for Arduino Core
 * Adapted from the official SDK.
 */

MEMORY
{
  ROM (rx)  : ORIGIN = 0x10000000, LENGTH = 0x200000  /* 2MB Flash */
  RAM (rwx) : ORIGIN = 0x30000000, LENGTH = 0x80000   /* 512KB SRAM */
}

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* The program code and other data goes into ROM */
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))  /* Startup code */
        *(.text)             /* .text sections (code) */
        *(.text*)            /* .text* sections (code) */
        *(.rodata)           /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)          /* .rodata* sections (constants, strings, etc.) */
        *(.glue_7)           /* glue arm to thumb code */
        *(.glue_7t)          /* glue thumb to arm code */
        *(.eh_frame)
        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(4);
        _etext = .;          /* define a global symbol at end of code */
    } > ROM

    /* Constant data goes into ROM */
    .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > ROM
    .ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > ROM

    _sidata = LOADADDR(.data);

    /* Initialized data sections go into RAM, load from ROM */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;        /* create a global symbol at data start */
        *(.data)           /* .data sections */
        *(.data*)          /* .data* sections */
        . = ALIGN(4);
        _edata = .;        /* define a global symbol at data end */
    } > RAM AT> ROM


    /* Uninitialized data section */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;         /* define a global symbol at bss start */
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;         /* define a global symbol at bss end */
        __bss_end__ = _ebss;
    } > RAM

    /* User stack section */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + 0x400; /* Minimum Heap Size */
        __HeapLimit = .;
        . = . + 0x1000; /* Minimum Stack Size */
        . = ALIGN(8);
        __StackLimit = .;
    } > RAM

    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}