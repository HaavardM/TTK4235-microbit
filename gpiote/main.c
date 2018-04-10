#include <stdint.h>
#include "gpio.h"
#include "ppi.h"
#include "gpiote.h"

#define A_PIN 17
#define B_PIN 26
#define MAT_P_1 13
#define MAT_P_2 14
#define MAT_P_3 15

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
        
        GPIOTE->CONFIG[0] = 1 | (A_PIN << 8) | (2 << 16); //INPUT - PIN_A - HIGH2LOW
        GPIOTE->CONFIG[1] = 3 | (MAT_P_1 << 8) | (3 << 16) | (1 << 20); //OUT - MAT_P_1 - TOGGLE
        GPIOTE->CONFIG[2] = 3 | (MAT_P_2 << 8) | (3 << 16) | (1 << 20); //OUT - MAT_P_2 - TOGGLE
        GPIOTE->CONFIG[3] = 3 | (MAT_P_3 << 8) | (3 << 16) | (1 << 20); //OUT - MAT_P_1 - TOGGLE
        PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
        PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);
        PPI->CHENSET = 1;
        
        for(int i = 0; i < 3; ++i) {
            PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->IN[0]);
            PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->OUT[i + 1]);
            PPI->CHENSET = (1 << i);
        }

	int sleep = 0;
	while(1) {
            sleep = 10000;
            while(--sleep);
	}
	return 0;
}
