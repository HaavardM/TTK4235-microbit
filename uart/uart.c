#include "uart.h"
#include "gpio.h"

#define PIN_TXD 24
#define PIN_RXD 25

#include "gpio.h"
#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t STARTRX;
    volatile uint32_t STOPRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVE1[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVE2[56];
    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVE3[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVE4;
    volatile uint32_t ERROR;
    volatile uint32_t RESERVE5[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVE6[110];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVE7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVE8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVE9;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVE10;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVE11[81];
    volatile uint32_t CONFIG;
} NRF_UART_REG;
    
    
void uart_init() {    
    //Set TX as output
    GPIO->DIRSET = 1 << PIN_TXD;
    //Set RX as input
    GPIO->DIRCLR = 1 << PIN_RXD;
    //Set TX to 1
    GPIO->OUTSET = 1 << PIN_TXD;
    //Set UART tx to tx pin
    UART->PSELTXD = PIN_TXD;
    //Set UART rx to rx pin
    UART->PSELRXD = PIN_RXD;
    //Disable CTS and RTS
    UART->PSELCTS = 0xFFFFFFFF;
    UART->PSELRTS = 0xFFFFFFFF;
    //Set baudrate
    UART->BAUDRATE = 9600;
    
    //Enable UART
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uart_send(char letter) {

}

void uart_read() {

}
