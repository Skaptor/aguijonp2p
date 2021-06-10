#ifndef WATER_TIMER_H
#define WATER_TIMER_H

typedef enum
{
    STATE_READ_EEPROM,
    STATE_WAIT_KEY,
    STATE_WAIT_KEY_RELEASE,
    STATE_COUNT,
    STATE_FINISH,
}WaterStates_t;

typedef struct
{
    uint8_t         lcdLine0[64];
    uint8_t         lcdLine1[64];

    uint32_t        seconds;
    uint32_t        tick;
    uint32_t        lcdTick;
    WaterStates_t   state;
    WaterStates_t   newState;
}WaterData_t;

void water_initialize(void);
void water_tasks(void);

#endif
