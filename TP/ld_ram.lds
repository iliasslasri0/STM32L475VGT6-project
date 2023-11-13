ENTRY(flash_to_sram)

MEMORY
	{
	  flash (wx) : ORIGIN = 0x08000000 LENGTH = 1M
	  sram1 (wx) : ORIGIN = 0x20000000 LENGTH = 96K
	  sram2 (wx) : ORIGIN = 0x10000000 LENGTH = 32K
	}

SECTIONS
{
	_load_text = LOADADDR(.text);
	.text : {
		_start_text = .;
		*(.IRQ)
		*(.text)
		. = ALIGN(4);
		_end_text = .;
		} > sram1 AT> flash

	.rodata : {
		*(.rodata)
		. = ALIGN(4);
		} AT> flash

	_load_data = LOADADDR(.data);
	.data : {
		_start_data = .;
		*(.data)
		. = ALIGN(4);
		_end_data = .;
		} > sram1 AT> flash

	.bss : {
		_bstart = . ;
		*(.bss) *(COMMON)
		_bend = . ;
		} > sram1

	.LOAD : {
		*(.LOAD)
		. = ALIGN(4);
		} AT> flash
}

_strt_stack = ORIGIN(sram2) + LENGTH(sram2);
