OUTPUT_FORMAT("elf32-littlearm")

MEMORY
{
  FLASH(rx):ORIGIN =0x00000000,LENGTH =256K
  SRAM(rwx):ORIGIN =0x20000000,LENGTH =32k
}

ENTRY(resetHandler)

SECTIONS
{
  .text :
  {
    *(.isr_vector)
    *(.text)
    *(.rodata)
    . = ALIGN(4);
    _etext = .;
  }> FLASH

  .data :
  {
    _sdata = .;
    *(.data)
    . = ALIGN(4);
    _edata = .;
  }> SRAM AT> FLASH

  .bss :
  {
    _sbss = .;
    *(.bss)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  }> SRAM
}