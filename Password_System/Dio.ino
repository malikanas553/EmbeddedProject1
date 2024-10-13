#include "Dio.h"

inline void Dio_SetRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  *Register |= (1 << Bit);
}

inline void Dio_ResetRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register & ~(1 << Bit);
}

inline void Dio_ToggleRegisterBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register ^ (1 << Bit);
}



