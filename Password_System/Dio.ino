//Digital/Input File containing functions for manipulating inputs and outputs

#include "Dio.h"

inline void Dio_SetRegisterBit(volatile unsigned char* Register, unsigned char Bit){ //Function for setting a bit to 1
  *Register |= (1 << Bit);
}

inline void Dio_ResetRegisterBit(volatile unsigned char* Register, unsigned char Bit){ //Function for setting a bit to 0
  *Register = *Register & ~(1 << Bit);
}

inline void Dio_ToggleRegisterBit(volatile unsigned char* Register, unsigned char Bit){// Function for toggling a bit
  *Register = *Register ^ (1 << Bit);
}



