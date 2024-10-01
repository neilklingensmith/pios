

#include <stdint.h>
#include "mmu.h"
#include "serial.h"
#include "rprintf.h"
#include "interrupt.h"
#include "timer.h"


extern struct table_descriptor_stage1 L1table[512];


void kernel_main() {


    esp_printf(putc, "Hello World!\r\n");

    interrupt_setup();
    timer_setup(1);

    asm("msr DAIFClr, #2"); // Enable IRQ
//    asm("udf #0xdead");
//    timer_setup();


    uint32_t *GPFSEL4 = (uint32_t*)0x3f200010;
    uint32_t *GPSET1 = (uint32_t*)0x3f200020;
    uint32_t *GPCLR1 = (uint32_t*)0x3f20002C;
    *GPFSEL4 |= (1<<6);

#if 0
    while(1) {
        *GPSET1 |= (1<<10);

        for(int k = 0; k < 0xfffffff; k++) {
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
        }
        *GPCLR1 |= (1<<10);
    }
#endif

    mapPages(0, 0);
    mapPages((void*)0x3f215000, (void*)0x3f215000); // map serial port
    mapPages((void*)CORE0_IRQ_SOURCE, (void*)CORE0_IRQ_SOURCE); // map IRQ_SOURCE
    loadPageTable(L1table);

    esp_printf(putc, "hello world from paging!\r\n");
    while(1){
    }
}
