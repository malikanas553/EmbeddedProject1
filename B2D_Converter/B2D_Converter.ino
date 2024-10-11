#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#define ZERO 0x7E
#define ONE 0x12
#define TWO 0xBC
#define THREE 0xB6
#define FOUR 0xD2
#define FIVE 0xE7
#define SIX 0xEF
#define SEVEN 0x32
#define EIGHT 0xFE
#define NINE  0xF6
#define OFF 0x00

int x = 1;
int decimal = 0;
int main(void) {
    init();

    while (1) {
        
        x = 0; 
        decimal = 0;
      
        while (x < 3) {
            if ((PINB & 0x01) == 1) { 
              PORTC = 0x10;
                switch (x) {
                    case 0: decimal += 4; break;
                    case 1: decimal += 2; break;
                    case 2: decimal += 1; break;
                }
              ++x; 
                while ((PINB & 0x01) == 1);
                PORTC = 0x00;
            } else if ((PINC & 0x01) == 1) {
              PORTC = 0x20;
                ++x;  
              while ((PINC & 0x01) == 1){};
              PORTC = 0x00;
            }
        }

       
        switch (decimal) {
            case 0: PORTD = ZERO; break;
            case 1: PORTD = ONE; break;
            case 2: PORTD = TWO; break;
            case 3: PORTD = THREE; break;
            case 4: PORTD = FOUR; break;
            case 5: PORTD = FIVE; break;
            case 6: PORTD = SIX; break;
            case 7: PORTD = SEVEN; break;
            default: PORTD = OFF; break;  
        }
        _delay_ms(5000);
        PORTD = OFF;     
    }
    return 0; 
}
void init(){
    DDRD = 0xFF;
    DDRC = 0x00;
    DDRB = 0X00;
    PORTB = 0X00;
    PORTC = 0x00;
    
}