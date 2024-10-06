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

int power(int x, int n) {
    int number = 1;
    for (int i = 0; i < n; ++i)
        number *= x;
    return number;
}

void displayNumber(int n){
   switch (n) {
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

}

void init() {
    DDRD = 0xFF;     
    DDRC = 0xFE;      
    DDRB = 0x00;     
    PORTB = 0x00;     
    PORTC = 0x00;     
}

int main(void) {
    init();
    int attempts = 3;
    int password = 7;
    while (attempts > 0) {
        int x = 2; 
        int decimal = 0;
        displayNumber(attempts);
        while (x >= 0) {
            if ((PINB & (1 << PINB0)) == 1) { 
                PORTC |= (1 << PORTC4); 
                decimal += power(2, x);
                --x; 
                while ((PINB & (1 << PINB0)) == 1); 
                _delay_ms(500);
                PORTC &= ~(1 << PORTC4); 
            } else if ((PINC & (1 << PINC0)) == 1) { 
                PORTC |= (1 << PORTC5); 
                --x;  
                while ((PINC & (1 << PINC0)) == 1); 
                _delay_ms(500); 
                PORTC &= ~(1 << PORTC5); 
            }
        }
      if(decimal == password){
       break;
      }else{
        PORTC |= 1 << PORTC2;
       _delay_ms(2000);
        PORTC = OFF;
        --attempts;
      }
    }
  if(attempts > 0){
  PORTC |= 1 << PORTC3;
  _delay_ms(2000);
    PORTC = OFF;}
    return 0; 
}