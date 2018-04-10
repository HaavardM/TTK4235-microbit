#ifndef UART_H
#define UART_H
#include<stdio.h>
void uart_init();
void uart_send(char letter);
char uart_read();

ssize_t _write(int fd, const void *buf, size_t count);
#endif
