#ifndef PIMNGR_H_
#define PIMNGR_H_

typedef enum {Initial, ReadytoRecognize, ReadytoReceive, BusytoRecognize, BusytoReceive, WaitingForData, ReceptionDone} PiStates;

uint8_t ID;
uint8_t DataLen;
uint8_t Data[18];

void PiMngr_GetStatus(void);
void PiMngr_StartRecognition(void);
void PiMngr_RequestData(void);
void PiMngr_TxDone(void);
void PiMngr_RxDone(void);

#endif /* PIMNGR_H_ */
