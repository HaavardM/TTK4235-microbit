#include <stdint.h>
#include "twi.h"
#include <stdlib.h>

#define GPIO ((NRF_GPIO_REGS*) 0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
    // Configure LED Matrix
    for(int i = 4; i <= 15; i++){
        GPIO->DIRSET = (1 << i);
        GPIO->OUTCLR = (1 << i);
    }
    uint8_t* data = (uint8_t*)malloc(8 * sizeof(uint8_t));
    twi_init();
    twi_multi_read(0x1D, 0x0D, 1, data);
    if(data[0] == 0x5A) {
        GPIO->OUTSET = (1 << 15);
    }
    int sleep = 0;
    while(1) {
        sleep = 10000;
        while(--sleep);
    }
    return 0;
}
