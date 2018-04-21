
#include "encoder_thread.h"

void encoder_queue_create (void){
	 encoder.eQueue = xQueueCreate( 32, sizeof(struct encoder_message));
     xQueueReset(encoder.eQueue);
}

void encoder_sensor_send(uint32_t L, uint32_t R){
    struct encoder_message peMessage;
    peMessage.left  = L;
	peMessage.right = R;
	xQueueSend( encoder.eQueue, ( void * ) &peMessage, (TickType_t) 0);
}

void calculate_encoder_val(void){
    encoder.int_left  = DRV_TMR1_CounterValueGet();///180;
    encoder.int_right = DRV_TMR2_CounterValueGet();///180; // x/180
    DRV_TMR1_CounterClear();
    DRV_TMR2_CounterClear();
    motor_data_send(encoder.int_left, encoder.int_right, motor.leftDir, motor.rightDir);
}
    

struct encoder_message* encoder_sensor_receive(void){
    struct encoder_message *inMessage;
	if(xQueueReceive( encoder.eQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void Encoder_Initialize(void){
    encoder_queue_create();
    DRV_TMR1_CounterClear();
    DRV_TMR2_CounterClear();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
}

void Encoder_Tasks(void){
    
    while(1){
        vTaskDelay(500);
        calculate_encoder_val();
        }
}
/*******************************************************************************
 End of File
 */