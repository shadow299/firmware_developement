ENTRY(Reset_Handler)

MEMORY {
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {
	.text : {
		*(.isr_vector)
		*(.text*)
	} > FLASH
	
	.bss : {
		*(.bss*)
	} > RAM
	
	_stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
