#include "data_thread.h"

void Data_Initialize(void){
    data_queue_create();
    data.seq = 0;
}

void data_queue_create(void){
     data.dataQueue = xQueueCreate( 32, sizeof(struct data_message));
     data.dataReady = xQueueCreate (10, sizeof(bool));
     xQueueReset(data.dataQueue);
     xQueueReset(data.dataReady);
}
void encoder_data_send(uint32_t L, uint32_t R){    
    struct data_message pdataMessage;
    pdataMessage.messageType = Encoder;
    pdataMessage.speed_left  = L;
	pdataMessage.speed_right = R;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}

void distance_data_send(uint32_t d){
    struct data_message pdataMessage;
    pdataMessage.messageType = Distance;
    pdataMessage.distance = d;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}
void color_data_send(int8_t c){
    struct data_message pdataMessage;
    pdataMessage.messageType = Color;
    pdataMessage.color = c;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}

void line_data_send(bool l0, bool l1, bool l2, bool l3, bool l4, bool l5, bool l6, bool l7){
    struct data_message pdataMessage;
    pdataMessage.messageType = Line;
    pdataMessage.l[0] = l0;
    pdataMessage.l[1] = l1;
    pdataMessage.l[2] = l2;
    pdataMessage.l[3] = l3;
    pdataMessage.l[4] = l4;
    pdataMessage.l[5] = l5;
    pdataMessage.l[6] = l6;
    pdataMessage.l[7] = l7;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}

void raw_line_data_send(int l0, int l1, int l2, int l3, int l4, int l5, int l6, int l7){//uint16_t l0, uint16_t l1, uint16_t l2, uint16_t l3, uint16_t l4, uint16_t l5, uint16_t l6, uint16_t l7){
    struct data_message pdataMessage;
    pdataMessage.messageType = Line_Raw;
    pdataMessage.line0 = l0;
    pdataMessage.line1 = l1;
    pdataMessage.line2 = l2;
    pdataMessage.line3 = l3;
    pdataMessage.line4 = l4;
    pdataMessage.line5 = l5;
    pdataMessage.line6 = l6;
    pdataMessage.line7 = l7;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}


void motor_data_send(uint32_t speed_left, uint32_t speed_right, bool direction_left, bool direction_right){
    struct data_message pdataMessage;
    pdataMessage.messageType = Motor;
    pdataMessage.speed_left = speed_left;
    pdataMessage.speed_right = speed_right;
    pdataMessage.direction_left = direction_left;
    pdataMessage.direction_right = direction_right;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}/*
void uart_data_send_send(char * c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Uart_send;
    dataMessage.uart = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void uart_data_receive_send(char * c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Uart_receive;
    dataMessage.uart = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
*/
void encoder_counter_rollover_error(void){
    struct data_message pdataMessage;
    pdataMessage.messageType = Rollover_error;
	xQueueSend( data.dataQueue, ( void * ) &pdataMessage, (TickType_t) 0);
}

struct data_message * data_receive( void ){
    struct data_message *inMessage;
	if(xQueueReceive( data.dataQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void DATA_Tasks(void){
    for(;;){
        struct data_message inDataMessage;
        if(xQueueReceive( data.dataQueue, ( void * ) &(inDataMessage), (TickType_t) 0)){
            if(inDataMessage.messageType == Motor){
                char *motor_string_0 = "{\"typ\":\"m\",\"rid\":\"1\",\"seq\":\"\0";
                char  motor_string_1[5]; itoa(motor_string_1, data.seq, 10); motor_string_1[4] = '\0';
                char *motor_string_2 = "\",\"dil\":\"\0";
                char motor_string_3[2]; itoa(motor_string_3, inDataMessage.direction_left, 10); motor_string_3[1] = '\0';
                char *motor_string_4 = "\",\"dir\":\"\0";
                char motor_string_5[2]; itoa(motor_string_5, inDataMessage.direction_right, 10); motor_string_5[1] = '\0';
                char *motor_string_6 = "\",\"spl\":\"\0";
                char motor_string_7[4]; itoa(motor_string_7, inDataMessage.speed_left*300/900, 10); motor_string_7[3] = '\0';
                char *motor_string_8 = "\",\"spr\":\"\0";
                char motor_string_9[4]; itoa(motor_string_9, inDataMessage.speed_right*300/900, 10); motor_string_9[3] = '\0';
                char *motor_string_10 = "\"}\0";
                transmitUARTstring(motor_string_0);
                transmitUARTstring(motor_string_1);
                transmitUARTstring(motor_string_2);
                transmitUARTstring(motor_string_3);
                transmitUARTstring(motor_string_4);
                transmitUARTstring(motor_string_5);
                transmitUARTstring(motor_string_6);
                transmitUARTstring(motor_string_7);
                transmitUARTstring(motor_string_8);
                transmitUARTstring(motor_string_9);
                transmitUARTstring(motor_string_10);
            }
            else if(inDataMessage.messageType == Color){
                char *color_string_0 = "{\"typ\":\"c\",\"rid\":\"1\",\"seq\":\"\0";
                char  color_string_1[5]; itoa(color_string_1, data.seq, 10); color_string_1[4] = '\0';
                char *color_string_2 = "\",\"col\":\"\0";
                char color_string_3[2]; itoa(color_string_3, inDataMessage.color, 10); color_string_3[1] = '\0';
                char *color_string_4 = "\"}\0";
                transmitUARTstring(color_string_0);
                transmitUARTstring(color_string_1);
                transmitUARTstring(color_string_2);
                transmitUARTstring(color_string_3);
                transmitUARTstring(color_string_4);
            }
            else if(inDataMessage.messageType == Line){
                char *line_string_0 = "{\"typ\":\"l\",\"rid\":\"1\",\"seq\":\"\0";
                char  line_string_1[5]; itoa(line_string_1, data.seq, 10); line_string_1[4] = '\0';
                char *line_string_2 = "\",\"li0\":\"\0";
                char line_string_3[2]; itoa(line_string_3, (inDataMessage.l[0]), 2); line_string_3[1] = '\0';
                char *line_string_4 = "\",\"li1\":\"\0";
                char line_string_5[2]; itoa(line_string_5, (inDataMessage.l[1]), 2); line_string_5[1] = '\0';
                char *line_string_6 = "\",\"li2\":\"\0";
                char line_string_7[2]; itoa(line_string_7, (inDataMessage.l[2]), 2); line_string_7[1] = '\0';
                char *line_string_8 = "\",\"li3\":\"\0";
                char line_string_9[2]; itoa(line_string_9, (inDataMessage.l[3]), 2); line_string_9[1] = '\0';
                char *line_string_10 = "\",\"li4\":\"\0";
                char line_string_11[2]; itoa(line_string_11, (inDataMessage.l[4]), 2); line_string_11[1] = '\0';
                char *line_string_12 = "\",\"li5\":\"\0";
                char line_string_13[2]; itoa(line_string_13, (inDataMessage.l[5]), 2); line_string_13[1] = '\0';
                char *line_string_14 = "\",\"li6\":\"\0";
                char line_string_15[2]; itoa(line_string_15, (inDataMessage.l[6]), 2); line_string_15[1] = '\0';
                char *line_string_16 = "\",\"li7\":\"\0";
                char line_string_17[2]; itoa(line_string_17, (inDataMessage.l[7]), 2); line_string_17[1] = '\0';
                char *line_string_18 = "\"}\0";
                transmitUARTstring(line_string_0);
                transmitUARTstring(line_string_1);
                transmitUARTstring(line_string_2);
                transmitUARTstring(line_string_3);
                transmitUARTstring(line_string_4);
                transmitUARTstring(line_string_5);
                transmitUARTstring(line_string_6);
                transmitUARTstring(line_string_7);
                transmitUARTstring(line_string_8);
                transmitUARTstring(line_string_9);
                transmitUARTstring(line_string_10);
                transmitUARTstring(line_string_11);
                transmitUARTstring(line_string_12);
                transmitUARTstring(line_string_13);
                transmitUARTstring(line_string_14);
                transmitUARTstring(line_string_15);
                transmitUARTstring(line_string_16);
                transmitUARTstring(line_string_17);
                transmitUARTstring(line_string_18);
            }
            else if(inDataMessage.messageType == Line_Raw){
                char *line_string_0 = "{\"typ\":\"r\",\"rid\":\"1\",\"seq\":\"\0";
                char  line_string_1[5]; itoa(line_string_1, data.seq, 10); line_string_1[4] = '\0';
                char *line_string_2 = "\",\"li0\":\"\0";
                char line_string_3[11]; itoa(line_string_3, inDataMessage.line0, 10); line_string_3[10] = '\0';
                char *line_string_4 = "\",\"li1\":\"\0";
                char line_string_5[11]; itoa(line_string_5, inDataMessage.line1, 10); line_string_5[10] = '\0';
                char *line_string_6 = "\",\"li2\":\"\0";
                char line_string_7[11]; itoa(line_string_7, inDataMessage.line2, 10); line_string_7[10] = '\0';
                char *line_string_8 = "\",\"li3\":\"\0";
                char line_string_9[11]; itoa(line_string_9, inDataMessage.line3, 10); line_string_9[10] = '\0';
                char *line_string_10 = "\",\"li4\":\"\0";
                char line_string_11[11]; itoa(line_string_11, inDataMessage.line4, 10); line_string_11[10] = '\0';
                char *line_string_12 = "\",\"li5\":\"\0";
                char line_string_13[11]; itoa(line_string_13, inDataMessage.line5, 10); line_string_13[10] = '\0';
                char *line_string_14 = "\",\"li6\":\"\0";
                char line_string_15[11]; itoa(line_string_15, inDataMessage.line6, 10); line_string_15[10] = '\0';
                char *line_string_16 = "\",\"li7\":\"\0";
                char line_string_17[11]; itoa(line_string_17, inDataMessage.line7, 10); line_string_17[10] = '\0';
                char *line_string_18 = "\"}\0";
                transmitUARTstring(line_string_0);
                transmitUARTstring(line_string_1);
                transmitUARTstring(line_string_2);
                transmitUARTstring(line_string_3);
                transmitUARTstring(line_string_4);
                transmitUARTstring(line_string_5);
                transmitUARTstring(line_string_6);
                transmitUARTstring(line_string_7);
                transmitUARTstring(line_string_8);
                transmitUARTstring(line_string_9);
                transmitUARTstring(line_string_10);
                transmitUARTstring(line_string_11);
                transmitUARTstring(line_string_12);
                transmitUARTstring(line_string_13);
                transmitUARTstring(line_string_14);
                transmitUARTstring(line_string_15);
                transmitUARTstring(line_string_16);
                transmitUARTstring(line_string_17);
                transmitUARTstring(line_string_18);
            }
            else if(inDataMessage.messageType == Distance){
                char *distance_string_0 = "{\"typ\":\"d\",\"rid\":\"1\",\"seq\":\"\0";
                char  distance_string_1[5]; itoa(distance_string_1, data.seq, 10); distance_string_1[4] = '\0';
                char *distance_string_2 = "\",\"di1\":\"\0";
                char distance_string_3[5]; itoa(distance_string_3, inDataMessage.distance, 10); distance_string_3[4] = '\0';
                char *distance_string_4 = "\"}\0";
                transmitUARTstring(distance_string_0);
                transmitUARTstring(distance_string_1);
                transmitUARTstring(distance_string_2);
                transmitUARTstring(distance_string_3);
                transmitUARTstring(distance_string_4);
            }
            
            
        }
        else {
            char *empty_string_0 = "{\"typ\":\"n\",\"rid\":\"1\",\"seq\":\"\0";
            char  empty_string_1[5]; itoa(empty_string_1, data.seq, 10); empty_string_1[4] = '\0';
            char *empty_string_2 = "\"}\0";
            transmitUARTstring(empty_string_0);
            transmitUARTstring(empty_string_1);
            transmitUARTstring(empty_string_2);
        }
        data.seq++;
        if(data.seq > 9999) data.seq = 0;
        vTaskDelay(DATA_RATE/portTICK_PERIOD_MS);
    }
}


/*******************************************************************************
 End of File
 */