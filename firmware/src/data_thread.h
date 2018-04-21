#ifndef _DATA_H    /* Guard against multiple inclusion */
#define _DATA_H

#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>
#include "encoder_thread.h"
#include "uart_thread.h"
#include "line_thread.h"
#include "motor_thread.h"

#define DATA_RATE 63 //date rate in ms

typedef struct
{
    QueueHandle_t dataQueue;
    QueueHandle_t dataReady;
    int16_t seq;
    TickType_t dataDelay;
} DATA_QUEUE_DATA;

DATA_QUEUE_DATA data;

struct data_message
    {
        enum message_t { Encoder, Distance, Color, Line, Motor, Rollover_error, Line_Raw } messageType;
        uint32_t distance;
        enum color_t { red, green, blue, black } color;
        uint8_t line;
        bool l[8];
        uint16_t speed_left;
        uint16_t speed_right;
        bool direction_left;
        bool direction_right;
        /*uint16_t line0;
        uint16_t line1;
        uint16_t line2;
        uint16_t line3;
        uint16_t line4;
        uint16_t line5;
        uint16_t line6;
        uint16_t line7;
        */
        int line0;
        int line1;
        int line2;
        int line3;
        int line4;
        int line5;
        int line6;
        int line7;
    } dataMessage;


void data_queue_create(void);
void encoder_data_send(uint32_t L, uint32_t R); 
void distance_data_send(uint32_t d);
void color_data_send(int8_t c);
void line_data_send(bool l0, bool l1, bool l2, bool l3, bool l4, bool l5, bool l6, bool l7);
void raw_line_data_send(int l0, int l1, int l2, int l3, int l4, int l5, int l6, int l7);//uint16_t l0, uint16_t l1, uint16_t l2, uint16_t l3, uint16_t l4, uint16_t l5, uint16_t l6, uint16_t l7);
void motor_data_send(uint32_t speed_left, uint32_t speed_right, bool direction_left, bool direction_right);
//void uart_data_send_send(char * c);
//void uart_data_receive_send(char * c);
void encoder_counter_rollover_error(void);
struct data_message * data_receive( void );
void Data_Initialize(void);
void DATA_Tasks(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
#endif

#endif