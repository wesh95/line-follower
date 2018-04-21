/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled state
    machines.

  Description:
    This file contains source code necessary to maintain system's polled state
    machines.  It implements the "SYS_Tasks" function that calls the individual
    "Tasks" functions for all the MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "system_definitions.h"


// *****************************************************************************
// *****************************************************************************
// Section: Local Prototypes
// *****************************************************************************
// *****************************************************************************


 
static void _SYS_Tasks ( void );
void _SYS_TMR_Tasks(void);
 
static void _UART_Tasks(void);

static void _LINE_Tasks(void);

static void _DATA_Tasks(void);

static void _MOTOR_Tasks(void);

static void _ENCODER_Tasks(void);
// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/

void SYS_Tasks ( void )
{
    /* Create OS Thread for Sys Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_Tasks,
                "Sys Tasks",
                1024, NULL, 0, NULL);


    /* Create task for System Timer state machine*/
    /* Create OS Thread for SYS_TMR Tasks. */
    xTaskCreate((TaskFunction_t) _SYS_TMR_Tasks,
                "SYS_TMR Tasks",
                1024, NULL, 1, NULL);
    
    /* Create OS Thread for UART Tasks. */
    xTaskCreate((TaskFunction_t) _UART_Tasks,
                "UART Tasks",
                4096, NULL, 1, NULL); 
    
    /* Create OS Thread for LINE Tasks. */
    xTaskCreate((TaskFunction_t) _LINE_Tasks,
                "Line Tasks",
                1024, NULL, 2, NULL); 

        /* Create OS Thread for DATA Tasks. */
    xTaskCreate((TaskFunction_t) _DATA_Tasks,
                "Data Tasks",
                4096, NULL, 1, NULL); 
    
        /* Create OS Thread for DATA Tasks. */
    xTaskCreate((TaskFunction_t) _MOTOR_Tasks,
                "Data Tasks",
                1024, NULL, 1, NULL); 
    
        /* Create OS Thread for DATA Tasks. */
    xTaskCreate((TaskFunction_t) _ENCODER_Tasks,
                "Encoder Tasks",
                1024, NULL, 1, NULL);
    /**************
     * Start RTOS * 
     **************/
    vTaskStartScheduler(); /* This function never returns. */
}


/*******************************************************************************
  Function:
    void _SYS_Tasks ( void )

  Summary:
    Maintains state machines of system modules.
*/
static void _SYS_Tasks ( void)
{
    while(1)
    {
        /* Maintain system services */

        /* Maintain Device Drivers */
 
 

        /* Maintain Middleware */

        /* Task Delay */
    }
}

void _SYS_TMR_Tasks(void)
{
    while(1)
    {
        SYS_TMR_Tasks(sysObj.sysTmr);
    }
 }

static void _UART_Tasks(void)
{
    while(1)
    {
        UART_Tasks();
    }
}

static void _LINE_Tasks(void)
{
    while(1)
    {
        LINE_Tasks();
    }
}

static void _DATA_Tasks(void)
{
    while(1)
    {
        DATA_Tasks();
    }
}

static void _MOTOR_Tasks(void)
{
    while(1)
    {
        MOTOR_Tasks();
    }
}

static void _ENCODER_Tasks(void)
{
    while(1)
    {
        Encoder_Tasks();
    }
}
/*******************************************************************************
 End of File
 */