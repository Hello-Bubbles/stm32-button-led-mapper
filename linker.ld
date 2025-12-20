ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
  SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_max_heap_size  = 0x400; /* A symbol declaration. Not a variable */
_max_stack_size = 0x200; /* A symbol declaration. Not a variable */

SECTIONS
{
. = ORIGIN(FLASH);

.isr_vector ALIGN(256) : AT(ORIGIN(FLASH))
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    
    *(.text)
    *(.rodata)
    end_of_text = .; /* Store the updated location counter value in the symbol 'end_of_text' */
  } > FLASH

  .data :
  {
    start_of_data = .;         /* Symbol marking the start of .data in SRAM */
    *(.data)
    end_of_data = .;
  } > SRAM AT > FLASH          /* VMA = SRAM, LMA = FLASH */

  .bss :
  {
    _sbss = .;
    *(.bss)
    _ebss = .;
  } > SRAM
}
