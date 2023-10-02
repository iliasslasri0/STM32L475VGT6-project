ENTRY(main)

MEMORY
	{
	  flash (wx) : ORIGIN = 0x08000000 LENGTH = 1M
	  sram1 (wx) : ORIGIN = 0x20000000 LENGTH = 96K
	  sram2 (wx) : ORIGIN = 0x10000000 LENGTH = 32K
	}

SECTIONS
 {
	.text : {
		*(.text)
		_etext = . ;
		} > sram1

	.rodata : {
		*(.rodata)
		} > sram1

	.data :  {
		_data = . ;
		*(.data)
		_edata = . ;
		} > sram1

	.bss : {
		_bstart = . ;
		*(.bss) *(COMMON)
		_bend = . ;
		} > sram1
}
