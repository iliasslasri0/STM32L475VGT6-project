ENTRY(_start)

MEMORY
	{
	  flash (wx) : ORIGIN = 0x08000000 LENGTH = 1M
	  sram1 (wx) : ORIGIN = 0x20000000 LENGTH = 96K
	  sram2 (wx) : ORIGIN = 0x10000000 LENGTH = 32K
	}

SECTIONS
{
	.IRQ : {
        *(.IRQ)
    	} AT> flash

	.text : {
		*(.text)
		} AT> flash

	.rodata : {
		*(.rodata)
		} > sram1 AT> flash

	.data : {
		*(.data)
		} > sram1 AT> flash

	.bss : {
		_bstart = . ;
		*(.bss) *(COMMON)
		_bend = . ;
		} > sram1
}

_strt_stack = ORIGIN(sram2) + LENGTH(sram2);
