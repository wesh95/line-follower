#include "uart_thread.h"

void uart_buffer_create (void){
	 uart.utQueue = xQueueCreate( 1024, sizeof(char));
     uart.urQueue = xQueueCreate( 1024, sizeof(char));
     xQueueReset(uart.utQueue);
     xQueueReset(uart.urQueue);
}

void uart_send(char data){
	xQueueSendToBack( uart.utQueue, ( void * ) &data, (BaseType_t) 0);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
}

char uart_receive(void){
    if( xQueueReceive( uart.urQueue, ( void * ) &uart.receive_char, portMAX_DELAY ) ){
        return uart.receive_char;
    }
}

char uart_receive_from_transmit_queue(void){
    if( xQueueReceiveFromISR( uart.utQueue, ( void * ) &uart.isr_transmit_char, pdFALSE ) );
    return uart.isr_transmit_char;
}

void uart_send_to_receive_queue(char data){
	xQueueSendToBackFromISR( uart.urQueue, ( void * ) &data, (TickType_t) 0);
}

void UART_Initialize(void){
    uart_buffer_create();
    PLIB_USART_Enable (USART_ID_1);
}

void transmitUARTstring(char *string){
    char *stringPointer;
    stringPointer = string;
    int transmitMax = 0;
    while(*stringPointer != '\0' & transmitMax < 1020){
            xQueueSendToBack( uart.utQueue, ( void * ) &*stringPointer, (TickType_t) 0);
            stringPointer++;
            transmitMax++;
    }
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
}

void UART_Tasks(void){
    //transmitUARTstring("Startup Success\n\r\0");
    for(;;){
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
/*******************************************************************************
 End of File
 */