#include "system.h"
#include "miwi/miwi_api.h"
#include "miwi/miwi_nvm.h"
#include "oc1.h"

typedef enum
{
    WAIT_MSG,
    PROCESS,
    RESPOND,
}Tastate_t;

Tastate_t state = WAIT_MSG;

void ta_tasks(void)
{
    switch(state){
        case WAIT_MSG:
            if(!MiApp_MessageAvailable()){
                break;                
            }                        
            
            state = PROCESS;            
            
        case PROCESS:
            switch(rxMessage.Payload[0]){
                case 0:
                    OC1_Stop();                   
                    OC1_PrimaryValueSet(0x1F40);
                    OC1_SecondaryValueSet(0x3E80);
                    OC1_Start();
                    DELAY_milliseconds(50);
                    OC1_Stop();                   
                    break;
                    
                case 1:
                    break;
            }
            
            MiApp_DiscardMessage();
            
            state = RESPOND;
            break;
            
        case RESPOND:
            MiApp_FlushTx();
            MiApp_WriteData(0x03);
            MiApp_WriteData(0x7F);
            if(MiApp_BroadcastPacket(false) == false){
                LCD_putStr(1,0, "FAIL :(", false);
            }     
            
            state = WAIT_MSG;
            break;
    }
}

