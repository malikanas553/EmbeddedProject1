//This is a password system based on a binary to digital converter

#include "Dio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "UART.h"

//Maximum buffer size for commands sent to UART
#define MAX_SIZE 100

// Function for applying x to the power of n
int power(int x, int n) {
    int number = 1;
    for (int i = 0; i < n; ++i)
        number *= x;
    return number;
}

// Function for displaying integer n on 7-segment display
void displayNumber(int n) {
    switch (n) {
        case 0: PORTD = ZERO; PORTB = 0x04; break;
        case 1: PORTD = ONE; PORTB = 0x04; break;
        case 2: PORTD = TWO; PORTB = 0x00; break;
        case 3: PORTD = THREE; PORTB = 0x04; break;
        case 4: PORTD = FOUR; PORTB = 0x04; break;
        case 5: PORTD = FIVE; PORTB = 0x04; break;
        case 6: PORTD = SIX; PORTB = 0x04; break;
        case 7: PORTD = SEVEN; PORTB = 0x04; break;
        default: PORTD = OFF; break;
    }
}
//Initialization Function
void init() {
    Uart_Init();
    DDRD = 0xFF; 
    DDRC = 0xFE; 
    DDRB = 0x04; 
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}

int main(void) {
    init();
    
    int password = 5; //Password in decimal form

    char command[MAX_SIZE];

    while (1) {
        //Wait for command from user
        Uart_ReadString(command, MAX_SIZE);

        if (!strcmp(command, "Commands")) { // Show list of commands
            Uart_SendString("LED_1_ON \nLED_1_OFF \nLED_2_ON \nLED_2_OFF \nStart \n");

        } else if (!strcmp(command, "LED_1_ON")) { //Turn on First LED
            Dio_SetRegisterBit(&PORTC, LED_1);

        } else if (!strcmp(command, "LED_1_OFF")) { //Turn off First LED
            Dio_ResetRegisterBit(&PORTC, LED_1);

        } else if (!strcmp(command, "LED_2_ON")) { //Turn on Second LED
            Dio_SetRegisterBit(&PORTC, LED_2);

        } else if (!strcmp(command, "LED_2_OFF")) { //Turn off Second LED
            Dio_ResetRegisterBit(&PORTC, LED_2);

        } else if (!strcmp(command, "Start")) { //Start the Password System

            int attempts = 3; //Number of attempts before shutdown
            init();

            //Keep running the function as long as attempts is not zero or user did not type correct password

            while (attempts > 0) {
                int x = 2; // X represents the counts of button left
                int decimal = 0;
                displayNumber(attempts);

                while (x >= 0) {
                    if (PINB & (1 << PINB0)) { //Check if button 1 is pressed

                        Uart_SendString("BUTTON_1_PRESSED\n");
                        Dio_SetRegisterBit(&PORTC, LED_1); //Turn on LED 1
                        decimal += power(2, x);
                        --x;
                        
                        while (PINB & (1 << PINB0)); //Wait until button is released

                        Uart_SendString("BUTTON_1_RELEASED\n");
                        _delay_ms(500);
                        Dio_ResetRegisterBit(&PORTC, LED_1); //Turn off LED 1

                    } else if (PINC & (1 << PINC0)) { //Check if button 2 is pressed

                        Dio_SetRegisterBit(&PORTC, LED_2); // Turn on LED 2
                        Uart_SendString("BUTTON_2_PRESSED\n");
                        --x;
                        
                        while (PINC & (1 << PINC0)); //Wait until button is released

                        Uart_SendString("BUTTON_2_RELEASED\n");
                        _delay_ms(500);
                        Dio_ResetRegisterBit(&PORTC, LED_2); //Turn off LED 2
                    }
                }

                if (decimal == password) { //check If correct password is inputed
                    break;
                } else {
                    Dio_SetRegisterBit(&PORTC, RED_LED); //Turn on RED LED
                    _delay_ms(2000);
                    PORTC = OFF;
                    --attempts; //Decrease attempts
                }
            }

            if (attempts > 0) { //If password is correct
                Uart_SendString("GREEN_LED_ON\n");
                Dio_SetRegisterBit(&PORTC, GREEN_LED);
                _delay_ms(2000);
                init();
            } else {
                displayNumber(attempts);
                Dio_SetRegisterBit(&PORTC, RED_LED);
                _delay_ms(3000);
                init();
            }

        } else { //If UART receives a command other than the above ones
            Uart_SendString("Not a valid command\n");
        }
    }

    return 0;
}
