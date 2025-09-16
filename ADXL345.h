#ifndef __ADXL345_H
#define __ADXL345_H

#include "stm32f3xx_hal.h"

void ADXL345_Init(void);
// inicjalizacja czujnika - wybor trybu pracy przez I2C (HAL)
void ADXL345_ReadXYZ(int16_t *x, int16_t *y, int16_t *z);
// odczyt wartosci przyspieszen x y z przez I2C (HAL)

#endif
