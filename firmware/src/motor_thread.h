
#ifndef _MOTOR_CONTROLER_H    /* Guard against multiple inclusion */
#define _MOTOR_CONTROLER_H

#include <stdbool.h>
#include <bsp.h>
#include "peripheral/oc/plib_oc.h"
#include "peripheral/int/plib_int.h"
/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define FORWARD true
#define REVERSE false

    typedef struct{
        float leftSpeed;
        float rightSpeed;
        uint32_t leftPower;
        bool leftDir;
        uint32_t rightPower;
        bool rightDir;
        uint32_t demo_int;
    } MOTOR_CONTROLLER_DATA;
    
    MOTOR_CONTROLLER_DATA motor;

    void setDirection(bool);
    void setDirectionL(bool);
    void setDirectionR(bool);
    
    void setPulseWidth(int);
    void setPulseWidthL(int);
    void setPulseWidthR(int);
    
    void setMotorL(bool, int);
    void setMotorR(bool, int);
    
    void Motor_Initialize(void);
    
    void MOTOR_Tasks(void);
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MOTOR_CONTROLER_H */

/* *****************************************************************************
 End of File
 */
