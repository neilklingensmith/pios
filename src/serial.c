
#include <stdint.h>


int putc(int data) {
    uint8_t *dreg = (uint8_t*)0x3f215040;

    *dreg = (char)data;

    return 0;
}
