#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

#include "Uart.h"



void SetBaudRate(unsigned short Baud){
  unsigned short UBBR = ((F_CPU/16) / Baud) - 1;
  UBRR0L = (UBBR & 0xFF);
  UBRR0H = ((UBBR >> 8) & 0xFF);
}

void Uart_Init(){

   SetBaudRate(9600);

   UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

   UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

}

void Uart_SendChar(unsigned char Character){
  while(!(UCSR0A & ( 1 << UDRE0 )));
  UDR0 = Character;
}

void Uart_SendString(const char *String){
  for (int i = 0; String[i] != '\0'; i++) {
        Uart_SendChar(String[i]);  
}
}

unsigned char Uart_ReadChar(void){
   while ( ! (UCSR0A & ( 1 << RXC0)) );
   return UDR0;
}

unsigned int Uart_ReadInt(void){
   while ( ! (UCSR0A & ( 1 << RXC0)) );
   return UDR0;
}


char Uart_ReadString(char *string, int maxSize) {
    unsigned char receivedChar;
    int i = 0;
    // Read characters until we reach a newline, carriage return, or buffer limit
    while (i < (maxSize - 1)) {
        receivedChar = Uart_ReadChar();  // Read a character from UART

        // Break if newline or carriage return is received
        if (receivedChar == '\n' || receivedChar == '\r') {
            break;
        }
            string[i] = receivedChar;
            i++;
    }
    string[i] = '\0';
}

