#include <stdint.h>

extern int main(void);

// defined in linker
extern uint32_t _stack_top;

void Reset_Handler(void);

// vector table
__attribute__((section(".isr_vector")))
uint32_t vector_table[] = {
	(uint32_t)&_stack_top, // initial stack pointer
	(uint32_t)Reset_Handler};

void Reset_Handler(void)
{
	main();
	while (1)
		;
}
