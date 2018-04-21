
#include "line_thread.h"

void Line_Initialize(void){
    DRV_TMR3_CounterClear();
    DRV_TMR3_Start();
}

void lineSensorSetOutputBits(void){
    PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B,  0xFF00);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_8,  1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9,  1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10, 1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11, 1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12, 1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13, 1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_14, 1);
    PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15, 1);
}
void lineSensorSetInputBits(void){
    PLIB_PORTS_DirectionInputSet( PORTS_ID_0, PORT_CHANNEL_B,  0xFF00);
}

void LINE_Tasks(void){
    //transmitUARTstring("line_read_start\n\0");
    for (line.i = 0; line.i < 8; line.i++){
        line.time[line.i] = 0;
        line.read[line.i] = false;
    }
    lineSensorSetOutputBits();
    vTaskDelay(250/portTICK_PERIOD_MS);
    line.rollover = false;
    DRV_TMR3_CounterClear();
    lineSensorSetInputBits();
    while(!line.rollover & (!line.read[0] | !line.read[1] | !line.read[2] | !line.read[3] | !line.read[4] | !line.read[5] | !line.read[6] | !line.read[7] )){
        if ( !lineBit0 & !line.read[0]){
            line.read[0] = true;
            line.time[0] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit1 & !line.read[1]){
            line.read[1] = true;
            line.time[1] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit2 & !line.read[2]){
            line.read[2] = true;
            line.time[2] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit3 & !line.read[3]){
            line.read[3] = true;
            line.time[3] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit4 & !line.read[4]){
            line.read[4] = true;
            line.time[4] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit5 & !line.read[5]){
            line.read[5] = true;
            line.time[5] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit6 & !line.read[6]){
            line.read[6] = true;
            line.time[6] = DRV_TMR3_CounterValueGet();
        }
        if ( !lineBit7 & !line.read[7]){
            line.read[7] = true;
            line.time[7] = DRV_TMR3_CounterValueGet();
        }
    }
    if (line.rollover){
        for ( line.i = 0; line.i < 8; line.i++ ){
            if( !line.read[line.i] ) line.time[line.i] = 65535;
        }
    }
    line_data_send( line.time[0] > LINE_CUTOFF,  line.time[1] > LINE_CUTOFF,  line.time[2] > LINE_CUTOFF,  line.time[3] > LINE_CUTOFF,  line.time[4] > LINE_CUTOFF,  line.time[5] > LINE_CUTOFF,  line.time[6] > LINE_CUTOFF,  line.time[7] > LINE_CUTOFF );
    //line_data_send(0,1,0,1,0,1,0,1);
    //raw_line_data_send(DRV_TMR3_CounterValueGet(), DRV_TMR3_CounterValueGet(), DRV_TMR3_CounterValueGet(), DRV_TMR3_CounterValueGet(), DRV_TMR3_CounterValueGet(), DRV_TMR3_CounterValueGet(), DRV_TMR3_CounterValueGet());
    //raw_line_data_send( line.time[0],  line.time[1],  line.time[2],  line.time[3],  line.time[4],  line.time[5],  line.time[6],  line.time[7] );
    //raw_line_data_send(1, 2, 3, 4,5,6,7,8);
}