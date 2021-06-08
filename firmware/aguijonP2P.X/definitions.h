#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include <xc.h>
#include <stdbool.h>
#include <stddef.h>
#include "spi.h"
#include "console.h"
#include "symbol.h"
#include "timer.h"
#include "delay.h"

/************************ DATA TYPE *******************************/

// DOM-IGNORE-BEGIN
/*********************************************************************
 Overview: Data types for drivers. This will facilitate easy
           access smaller chunks of larger data types when sending
           or receiving data (for example byte sized send/receive
           over parallel 8-bit interface.
*********************************************************************/
// DOM-IGNORE-END
typedef union
{

    uint8_t  v[4];
    uint16_t w[2];
    uint32_t Val;

}API_UINT32_UNION;

typedef union
{

    uint8_t  v[2];
    uint16_t Val;

}API_UINT16_UNION;

    
#define MAIN_RETURN int

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencySystemGet()
*
* Overview: This macro returns the system clock frequency in Hertz.
*
*
********************************************************************/

#define SYS_CLK_FrequencySystemGet()    (8000000)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyPeripheralGet()
*
* Overview: This macro returns the peripheral clock frequency
*			used in Hertz.
*
*
********************************************************************/

#define SYS_CLK_FrequencyPeripheralGet()    (SYS_CLK_FrequencySystemGet()/2)

/*********************************************************************
* Macro: #define	SYS_CLK_FrequencyInstructionGet()
*
* Overview: This macro returns instruction clock frequency
*			used in Hertz.
*
*
********************************************************************/

#define SYS_CLK_FrequencyInstructionGet()   (SYS_CLK_FrequencySystemGet()/2)
#define FCY                                 (SYS_CLK_FrequencyInstructionGet())

#endif
