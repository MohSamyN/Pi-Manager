#include <stdint.h>
#include "PiMngr.h"
#include "PiMngr_Cfg.h"
#include "UART.h"
#include "UART_Cfg.h"

PiStates State = Initial;
static uint8_t RxBuff[20];
static uint8_t Flag;

static void DelayTx(void);
static void DelayRx(void);


void PiMngr_GetStatus(void)
{
    if(State == Initial)
    {
        UART_Tx_Init("Get Status", 10, UART_ChannelIdTx);
        DelayTx();
        UART_Tx(UART_ChannelIdTx);
    }
    else
    {
        /* Do nothing */
    }
}

void PiMngr_StartRecognition(void)
{
    if(State == ReadytoRecognize)
    {
        UART_Tx_Init("Start", 5, UART_ChannelIdTx);
        DelayTx();
        UART_Tx(UART_ChannelIdTx);
    }
    else
    {
        /* Do nothing */
    }
}

void PiMngr_RequestData(void)
{
    if(State == ReadytoReceive)
    {
        State = WaitingForData;
        UART_Tx_Init("Send", 4, UART_ChannelIdTx);
        DelayTx();
        UART_Tx(UART_ChannelIdTx);
    }
    else
    {

    }
}

void PiMngr_TxDone(void)
{
    uint8_t LoopIndex;
    uint32_t LoopIndex2;
    if(State == Initial)
    {
        UART_Rx_Init(RxBuff, 5, UART_ChannelIdRx);
        DelayRx();
        for(LoopIndex = 0; LoopIndex < 5; LoopIndex++)
        {
            UART_Rx(UART_ChannelIdRx);
        }
    }
    else if(State == ReadytoRecognize)
    {
        UART_Rx_Init(RxBuff, 4, UART_ChannelIdRx);
        DelayRx();
        Flag = 0;
        for(LoopIndex2 = 0; (LoopIndex2 < 5000000) && (Flag == 0); LoopIndex2++)
        {
            for(LoopIndex = 0; LoopIndex < 4; LoopIndex++)
            {
                UART_Rx(UART_ChannelIdRx);
            }
        }
    }
    else if(State == WaitingForData)
    {
        UART_Rx_Init(RxBuff, 11, UART_ChannelIdRx);
        DelayRx();
        for(LoopIndex = 0; LoopIndex < 11; LoopIndex++)
        {
            UART_Rx(UART_ChannelIdRx);
        }
    }
    else if(State == ReceptionDone)
    {
        DelayRx();
        ID = RxBuff[0];
        DataLen = RxBuff[1];
        for(LoopIndex = 0; LoopIndex < DataLen; LoopIndex++)
        {
            Data[LoopIndex] = RxBuff[LoopIndex + 2];
        }
        State = Initial;
    }
    else
    {
        /* Do nothing */
    }

}

void PiMngr_RxDone(void)
{
    if(State == Initial)
    {
        if((RxBuff[0] == 'R') && (RxBuff[1] == 'e') && (RxBuff[2] == 'a') && (RxBuff[3] == 'd') && (RxBuff[4] == 'y'))
        {
            State = ReadytoRecognize;
        }
        else
        {
            State = BusytoRecognize;
        }
    }
    else if(State == ReadytoRecognize)
    {
        Flag = 1;
        if((RxBuff[0] == 'D') && (RxBuff[1] == 'o') && (RxBuff[2] == 'n') && (RxBuff[3] == 'e'))
        {
            State = ReadytoReceive;
        }
        else
        {
            State = BusytoReceive;
        }
    }
    else if(State == WaitingForData)
    {
        State = ReceptionDone;
        UART_Tx_Init("Done", 4, UART_ChannelIdTx);
        DelayTx();
        UART_Tx(UART_ChannelIdTx);
    }
    else
    {
        /* Do nothing */
    }
}


static void DelayTx(void)
{
    uint64_t volatile LoopIndex;
    for(LoopIndex = 0; LoopIndex < 8001; LoopIndex++);
}

static void DelayRx(void)
{
    uint64_t volatile LoopIndex;
    for(LoopIndex = 0; LoopIndex < 65000; LoopIndex++);
}
