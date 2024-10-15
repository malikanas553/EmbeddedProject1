//Header file containing DIO functions
#ifndef __DIO__
#define __DIO__

//Numbers for Seven Segment

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

//LED Pins

#define RED_LED 2
#define GREEN_LED 3
#define LED_1 4
#define LED_2 5

inline void Dio_SetRegisterBit(volatile unsigned char* Register, unsigned char Bit);

inline void Dio_ResetRegisterBit(volatile unsigned char* Register, unsigned char Bit);

inline void Dio_ToggleRegisterBit(volatile unsigned char* Register, unsigned char Bit);


#endif /*__DIO__*/
