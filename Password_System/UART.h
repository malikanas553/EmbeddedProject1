//Header file for all UART functions
#ifndef __UART__
#define __UART__

void Uart_Init(void);

void SetBaudRate(unsigned short BuadRate);

void Uart_SendChar(unsigned char DataByte);

unsigned char Uart_ReadChar();

unsigned int Uart_ReadInt(void);

void Uart_SendString(const char *String);

char Uart_ReadString(char *string, int maxSize);

#endif