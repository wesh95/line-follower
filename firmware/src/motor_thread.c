
#include "motor_thread.h"
#include "uart_thread.h"

 
    void setDirection(bool dir){
        motor.leftDir = dir;
        motor.rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    void setDirectionL(bool dir){
        motor.leftDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        return;
    }
    void setDirectionR(bool dir){
        motor.rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    
    void setPulseWidth(int val){
            DRV_OC0_Stop();    
            DRV_OC1_Stop();
            motor.rightPower = val;
            motor.leftPower = val;
            PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
            PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
            DRV_OC0_Start();
            DRV_OC1_Start();
    }

    void setPulseWidthL(int val){
        DRV_OC0_Stop();
        motor.leftPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
        DRV_OC0_Start();
        return;
    }
    void setPulseWidthR(int val){
        DRV_OC1_Stop();
        motor.rightPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
        DRV_OC1_Start();
        return;
    }
    
    void setMotorL(bool dir, int val){
        DRV_OC0_Stop();
        if (val > 100) val = 100;
        motor.leftPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.leftDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, (uint16_t)val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        DRV_OC0_Start();
        return;
    }
    
    void setMotorR(bool dir, int val){
        DRV_OC1_Stop();
        if (val > 100) val = 100;
        motor.rightPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.rightDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, (uint16_t)val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        DRV_OC1_Start();
        return;
    }
    void Motor_Initialize(void){
        PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_C,  0x4000);
        PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_G,  0x0001);
        DRV_TMR0_Start();
        motor.leftSpeed = 0;
        motor.rightSpeed = 0;
        motor.leftDir = FORWARD;
        motor.rightDir = FORWARD;
        setMotorR(FORWARD, 0);
        setMotorL(FORWARD, 0);
    }

    void MOTOR_Tasks(void){
        Motor_Initialize();
        int state = 0;//idle
        char linedata = 'c';
        int right = 0;
        int left = 0;
        char lastLine ='c';
        char receive;

        for(;;){
            vTaskDelay(50);

            if(state == 0){ //if in idle state            
                if(linedata == '0'){//if not on line
                    state = 1;//change to line search

                }
                else if(linedata == 'c'){
                     //transmitUARTstring("{\"line\":\"center\"}");
                     setMotorR(FORWARD,50);
                     setMotorL(FORWARD,50);
                     lastLine = 'c';
                }
                else if (linedata == 'r'){
                    //transmitUARTstring("{\"line\":\"right\"}");
                    setMotorR(FORWARD,50);
                    setMotorL(REVERSE, 50);
                    lastLine = 'r';
                }
                else if(linedata =='l'){
                     //transmitUARTstring("{\"line\":\"left\"}");
                     setMotorL(FORWARD,50);
                     setMotorR(REVERSE, 50);
                     lastLine = 'l';
                }
              lastLine = linedata;
                          
            }
            else{

                if(lastLine == 'r'){
                    //transmitUARTstring("{\"line\":\"lost right\"}");
                    setMotorL(FORWARD,50);
                    setMotorR(REVERSE, 50);
                }
                else if(lastLine == 'l'){
                    //transmitUARTstring("{\"line\":\"lost left\"}");
                     setMotorR(FORWARD,50);
                     setMotorL(REVERSE, 50);
                }

                if(linedata != '0'){//line found
                    state = 0; //switch back to idle state
                }

            }
            linedata = uart_receive();

        }

       
    }
/* *****************************************************************************
 End of File
 */
