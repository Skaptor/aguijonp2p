#include "system.h"

static uint32_t tick = 0;
static void appTimerInterrupt(void)
{  
    tick++;
}

uint32_t tickGet(void)
{
    return tick;
}


void tickInit(void)
{
    TMR1_SetInterruptHandler(appTimerInterrupt);    
}

