#ifndef _UART_H    /* Guard against multiple inclusion */
#define _UART_H

#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>
#include "system_config.h"
#include "system_definitions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    QueueHandle_t utQueue;
    QueueHandle_t urQueue;
    char transmit_char;
    char isr_transmit_char;
    char isr_receive_char;
    char receive_char;
    char *ptr;
    char itoa[5];
    volatile bool ready;
} UART_DATA;

UART_DATA uart;

void uart_transmit_create(void);
void uart_send(char data);
char uart_receive(void);
char uart_receive_from_transmit_queue(void);
void uart_send_to_receive_queue(char data);
void UART_Initialize(void);
void transmitUARTstring(char *string);
void transmitUARTchar(char);
void UART_Tasks(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
#endif

#endif