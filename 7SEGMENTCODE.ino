#include <avr/io.h>
#include <util/delay.h>
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


int main(void){
  init();

  while (1)
  {
    PORTD = ZERO;
    _delay_ms(1000);
    PORTD = ONE;
    _delay_ms(1000);
    PORTD = TWO;
    _delay_ms(1000);
    PORTD = THREE;
    _delay_ms(1000);
    PORTD = FOUR;
    _delay_ms(1000);
    PORTD = FIVE;
    _delay_ms(1000);
    PORTD = SIX;
    _delay_ms(1000);
    PORTD = SEVEN;
    _delay_ms(1000);
    PORTD = EIGHT;
    _delay_ms(1000);
     PORTD = NINE;
    _delay_ms(1000);
     PORTD = OFF;
    _delay_ms(1000);
    
  }
  return 0; 
}

void init(){
    DDRD = 0xFF;
    
}