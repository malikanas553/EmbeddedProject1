#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

#include "Uart.h"



void SetBaudRate(unsigned short Baud){
  unsigned short UBBR = ((F_CPU/16) / Baud) - 1; //Formula for setting baud rate
  UBRR0L = (UBBR & 0xFF); //Set first 8 low bits
  UBRR0H = ((UBBR >> 8) & 0xFF); //Set the 8 most significant bits
}

void Uart_Init(){

   SetBaudRate(9600);

   UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //Enable Receiver and Transmitter

   UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //Set 8 frame data bits and 1 stop bit

}

void Uart_SendChar(unsigned char Character){
  while(!(UCSR0A & ( 1 << UDRE0 ))); // Wait until transmit buffer is empty
  UDR0 = Character;
}

void Uart_SendString(const char *String){
  for (int i = 0; String[i] != '\0'; i++) { //Loop through the string and send the characters one by one
        Uart_SendChar(String[i]);  
}
}

unsigned char Uart_ReadChar(void){  
   while ( ! (UCSR0A & ( 1 << RXC0)) ); //Wait until buffer has received data
   return UDR0;
}

unsigned int Uart_ReadInt(void){
   unsigned int value = 0;
   while ( ! (UCSR0A & ( 1 << RXC0)) ); 

   //Int is 16 bits so value is shifted to store it

   value = UDR0; // Store in first 8 bits

   value <<= 8;

   value |= UDR0; // Store in 8 lower bits

   return value;
}


char Uart_ReadString(char *string, int maxSize) {

    unsigned char receivedChar;
    int i = 0; 

    while (i < (maxSize - 1)) { //Loop continues as long as buffer is not full
        receivedChar = Uart_ReadChar();

        
        if (receivedChar == '\n' || receivedChar == '\r') { // Loop breaks when Uart receieves \n or \r
            break;
        }
            string[i] = receivedChar;
            i++;
    }

    string[i] = '\0'; //String end value
}

