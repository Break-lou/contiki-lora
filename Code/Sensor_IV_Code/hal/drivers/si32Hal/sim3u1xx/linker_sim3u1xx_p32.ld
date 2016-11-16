/*
* GENERATED FILE - DO NOT EDIT
* (C) Code Red Technologies Ltd, 2008-10
* Generated linker script file for SiM3U167
* Created from generic_c.ld (vRed Suite v4.5 (0_alpha [Build 21] [16/09/2011] ))
* By Red Suite v4.5.0_alpha [Build 21] [16/09/2011]  on Mon Oct 10 15:13:09 CDT 2011
*/

SEARCH_DIR(..)
INCLUDE "myLinkerOptions_p32.ld"

MEMORY
{
  /* Define each memory region */
  MFlash256 (rx) : ORIGIN = 0x0, LENGTH = 0x3fffc /* 255k */
  StandardRam28 (rwx) : ORIGIN = 0x20001000, LENGTH = 0x7000 /* 28k */
  RetentionRam4 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x1000 /* 4k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash256 = 0x0 + 0x3fffc;
  __top_StandardRam28 = 0x20001000 + 0x7000;
  __top_RetentionRam4 = 0x20000000 + 0x1000;

ENTRY(ResetISR)

SECTIONS
{

	/* MAIN TEXT SECTION */	
	.text : ALIGN(4)
	{
		FILL(0xff)
		KEEP(*(.isr_vector))
		
		/* Global Section Table */
		. = ALIGN(4) ;
		__section_table_start = .;
		__data_section_table = .;
		LONG(LOADADDR(.data));
		LONG(    ADDR(.data)) ;
		LONG(  SIZEOF(.data));
		LONG(LOADADDR(.data_RAM2));
		LONG(    ADDR(.data_RAM2)) ;
		LONG(  SIZEOF(.data_RAM2));
		__data_section_table_end = .;
		__bss_section_table = .;
		LONG(    ADDR(.bss));
		LONG(  SIZEOF(.bss));
		LONG(    ADDR(.bss_RAM2));
		LONG(  SIZEOF(.bss_RAM2));
		__bss_section_table_end = .;
		__section_table_end = . ;
		/* End of Global Section Table */
		

		*(.after_vectors*)
		
		*(.text*)
		*(.rodata .rodata.*)
		. = ALIGN(1024);
		
	} > MFlash256

	/*
	 * for exception handling/unwind - some Newlib functions (in common
	 * with C++ and STDC++) use this.
	 */
	.ARM.extab : ALIGN(4)
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > MFlash256
	__exidx_start = .;
	
	.ARM.exidx : ALIGN(4)
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > MFlash256
	__exidx_end = .;
	
	_etext = .;
		
	
	.data_RAM2 : ALIGN(4)
	{
	   FILL(0xff)
		*(.data.$RAM2*)
		*(.data.$RetentionRam4*)
	   . = ALIGN(4) ;
	} > RetentionRam4 AT>MFlash256
	
	/* MAIN DATA SECTION */

	.uninit_RESERVED : ALIGN(4)
	{
		KEEP(*(.bss.$RESERVED*))
	} > StandardRam28

	.data : ALIGN(4)
	{
		FILL(0xff)
		_data = .;
		*(vtable)
		*(.data*)
		. = ALIGN(4) ;
		_edata = .;
	} > StandardRam28 AT>MFlash256

	
	.bss_RAM2 : ALIGN(4)
	{
		*(.bss.$RAM2*)
		*(.bss.$RetentionRam4*)
	   . = ALIGN(4) ;
	} > RetentionRam4

	/* MAIN BSS SECTION */
	.bss : ALIGN(4)
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4) ;
		_ebss = .;
		PROVIDE(end = .);
	} > StandardRam28
	
	PROVIDE(_pvHeapStart = .);
	PROVIDE(_vStackTop = __top_StandardRam28 - 0);
} 
