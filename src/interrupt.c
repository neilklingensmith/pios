

#include <stdint.h>
#include "interrupt.h"
#include "serial.h"
#include "rprintf.h"

extern void Vector_table_el1();

void interrupt_setup() {
    asm("msr vbar_el1, %0"
        :
	: "r" (Vector_table_el1)
	:);
}

void handle_timer() {
}

void handle_irq() {
    switch (*CORE0_IRQ_SOURCE)
    {
    case 8:
      handle_timer();
      break;
    }
}
