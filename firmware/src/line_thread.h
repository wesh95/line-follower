
#ifndef _LINE_SENSOR_H    /* Guard against multiple inclusion */
#define _LINE_SENSOR_H

#include "FreeRTOS.h"
#include "system_config.h"
#include "system_definitions.h"
#include <stdbool.h>
#include "stdint.h"
#include "stdlib.h"

#define LINE_CUTOFF 2500

#define lineBit0 PORTBbits.RB8
#define lineBit1 PORTBbits.RB9
#define lineBit2 PORTBbits.RB10
#define lineBit3 PORTBbits.RB11
#define lineBit4 PORTBbits.RB12
#define lineBit5 PORTBbits.RB13
#define lineBit6 PORTBbits.RB14
#define lineBit7 PORTBbits.RB15



    typedef struct {
        int time[8];
        bool read[8];
        volatile bool rollover;
        uint8_t i;

    } LINE_SENSOR_DATA;
    
    LINE_SENSOR_DATA line;

    void Line_Initialize(void);
    void lineSensorSetOutputBits(void);
    void lineSensorSetInputBits(void);
    void LINE_Tasks(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus

#endif

#endif

/* *****************************************************************************
 End of File
 */
