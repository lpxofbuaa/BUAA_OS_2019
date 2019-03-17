OUTPUT_ARCH(mips)
/*
Set the architecture to mips.
*/
ENTRY(_start)
/*
Set the ENTRY point of the program to _start.
*/
SECTIONS
{
. = 0x80010000;
.text : { *(.text) }
. = 0x80400000;
.data : { *(.data) }
.bss : { *(.bss) }
end = . ;
}
