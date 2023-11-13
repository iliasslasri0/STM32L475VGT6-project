#include <stdint.h>
#include <stddef.h>

void *my_memset(void *s, int c,  unsigned int n);
int main();

extern uint8_t _bstart, _bend;
extern uint32_t _start_data, _end_data;
extern uint32_t _start_text, _end_text;
extern uint32_t _load_text;
extern uint32_t _load_data;



void flash_to_sram() __attribute__((section(".LOAD")));

void init_bss(){
	uint32_t size = &_bend - &_bstart;
	my_memset(&_bstart, 0, size);
}

void flash_to_sram(){
	uint32_t size_data = (uint32_t) &_end_data - (uint32_t) &_start_data;
	uint32_t size_text = (uint32_t) &_end_text - (uint32_t) &_start_text;

	uint32_t *str_data = &_start_data;
	uint32_t *load_data = &_load_data;

	for(; size_data>0; size_data--){
		*(str_data++) = *(load_data++);
	}

	uint32_t *str_text = &_start_text;
	uint32_t *load_text = &_load_text;

	for(; size_text>0; size_text--){
		*(str_text++) = *(load_text++);
	}

	init_bss();
	main();

}