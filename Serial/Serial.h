#ifndef  __Serial_h_
#define  __Serial_h_
#include <stdio.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNum(uint32_t Number,uint8_t Length);
void Serial_printf(char *format,...);
#endif
