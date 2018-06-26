#include <stdint.h>
#include "GPIO.h"
#include "UART.h"
#include "GPIO_Cfg.h"
#include "UART_Cfg.h"
#include "M4MemMap.h"
#include "PiMngr.h"


int main(void)
{
    GPIO_Init();
    UART_Init();
    while(1)
    {
        PiMngr_GetStatus();
        PiMngr_StartRecognition();
        PiMngr_RequestData();
    }
    return 0;
}

