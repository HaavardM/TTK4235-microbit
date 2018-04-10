#include "twi.h"

#define SDA_PIN 30
#define SCL_PIN 0
#define I2C_ADDRESS 0x1D 

#define TWIO ((NRF_TWI_REG*)0x40003000

typedef struct {
    volatile uint32_t STARTRX;
    volatile uint32_t RESERVE0;
    volatile uint32_t STARTTX;
    volatile uint32_t STARTRX;
    volatile uint32_t RESERVE1[2]; 
    volatile uint32_t STOP;
    volatile uint32_t RESERVE2;
    volatile uint32_t RESUME;
    volatile uint32_t RESERVE3[56];
    volatile uint32_t STOPPED;
    volatile uint32_t RXDREADY;
    volatile uint32_t RESERVE4[4];
    volatile uint32_t TXDSENT;
    volatile uint32_t RESERVE5;
    volatile uint32_t ERROR;
    volatile uint32_t RESERVE6[4];
    volatile uint32_t BB;
    volatile uint32_t RESERVE7[49];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVE8[63];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVE[110];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVE9[14];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVE10;
    volatile uint32_t PSELSCL;
    volatile uint32_t RESERVE11;
    volatile uint32_t PSELSDA;
    volatile uint32_t RESERVE12[2];
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVE13[2];
    volatile uint32_t FREQUENCY;
    volatile uint32_t RESERVE14[24];
    volatile uint32_t ADDRESS;
} NRF_TWI_REG;

void twi_init() {
    TWIO->FREQUENCY = 0x01980000;
    TWIO->PSELSCL = SCL_PIN;
    TWIO->PSELSDA = SDA_PIN;
    TWIO->ADDRESS = I2C_ADDRESS;
    TWIO->ENABLE = 5;
}

void twi_multi_read(uint8_t slave_address,
                    uint8_t start_register,
                    int size,
                    uint8_t * data_buffer) {
    TWIO->ADDRESS = slave_address;
    TWIO->STARTTX = 1;
    TWIO->TXD = start_register;
    while(!TWIO->TXDSENT);
    TWIO->TXDSENT = 0;
    TWIO->RXDREADY = 0;
    TWIO->STARTRX = 1;
    
    for(int i = 0; i < size - 1; ++i) {
        while(!TWIO->RXDREADY);
        data_buffer[i] = TWIO->RXD;
        TWIO->RXDREADY = 0;
    }
    TWIO->STOP;
    while(!TWIO->RXDREADY);
    data_buffer[size - 1] = TWIO->RXD;
}
