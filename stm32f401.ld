ENTRY(Reset_Handler)
MEMORY
{
  ROM (rx)  : ORIGIN = 0x08000000, LENGTH = 256K 
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))  
  } > ROM

  .text :
  { 
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
  } > ROM 

  _sidata = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
    _sdata = .; 
    *(.data*)
    . = ALIGN(4);
    _edata = .; 
  } > RAM AT> ROM 

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    . = ALIGN(4);
    _ebss = .;
  } > RAM 

  /DISCARD/ : { *(.ARM.exidx*) *(.comment)}
}
