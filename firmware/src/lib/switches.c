#include "system.h"
#include "switches.h"
#include "tick.h"
#include "pin_manager.h"

static SwitchTaskData_t swData;

uint8_t readPort(void)
{
    return 0x0F - ((IO_DIPSW3_GetValue() << 3) | (IO_DIPSW2_GetValue() << 2) | (IO_DIPSW1_GetValue() << 1) | IO_DIPSW0_GetValue());
}

void sw_initialize(void)
{
    swData.switchPort = 0x00;
    swData.state = STATE_READ;
}

bool sw_get(uint8_t idx)
{
    return swData.switchPort & (1<<idx);
}

uint8_t sw_getPort(void)
{
    return swData.switchPort;
}

void sw_tasks(void)
{
    uint8_t i;

    switch(swData.state){
        case STATE_READ:
            swData.unbounced1 = readPort();
            swData.tick = tickGet();
            swData.state = STATE_DEBOUNCE;
            break;

        case STATE_DEBOUNCE:
            if(tickGet()-swData.tick > 1){
                swData.switchPort = swData.unbounced1 & readPort();;
                swData.state = STATE_READ;                             
            }
            break;
    }
}

