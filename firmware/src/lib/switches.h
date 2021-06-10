#ifndef SWITCHES_H
#define SWITCHES_H

typedef enum
{
    STATE_READ,
    STATE_DEBOUNCE,
}SwitchTaskState_t;

typedef struct
{
    uint8_t             switchPort;
    uint8_t             unbounced1;
    uint8_t             unbounced2;
    uint32_t            tick;
    SwitchTaskState_t   state;
}SwitchTaskData_t;


void sw_initialize(void);
bool sw_get(uint8_t idx);
uint8_t sw_getPort(void);
void sw_tasks(void);

#endif
