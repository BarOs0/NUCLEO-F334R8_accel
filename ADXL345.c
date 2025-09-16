#include "ADXL345.h"

extern I2C_HandleTypeDef hi2c1;

#define ADXL345_ADDR (0x53 << 1)
// 0x53 -> adres czujnika gdy SDO <-> GND
// Przesuwam o 1 bit w lewo bo HAL obsluguje 8 bitowe I2C
// 1010011 << 1 = 10100110
// ten ostatni bit to flaga: 0 - zapis, 1 - odczyt
#define ADXL345_REG_POWER_CTL 0x2D
// pod takim adresem w dokumentacji czujnika bede wybieral tryb jego pracy.
// 0x08 - pomiar przyspieszenia
// 0x00 - tryb czuwania
// 0x10 - automatycznie przechodzi w tryb czuwania jak nic nie wykrywa
// 0x04 - tryb uspienia
// mozna laczyc
#define ADXL345_REG_DATAX0 0x32
// pod takim adresem beda pojawialy sie dane
// dane -> 16 bitowe, osie x,y,z: 0x32 - 0x37

void ADXL345_Init(void){
	uint8_t mode = 0x08; // tryb pomiarowy -> mode = 0x08
	HAL_I2C_Mem_Write(&hi2c1, ADXL345_ADDR, ADXL345_REG_POWER_CTL, 1, &mode , 1, 100);
}

void ADXL345_ReadXYZ(int16_t *x, int16_t *y, int16_t *z){
	uint8_t data[6];
	HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDR, ADXL345_REG_DATAX0, 1, data, 6, 100);

	*x = (int16_t)((data[1] << 8) | data[0]);
	*y = (int16_t)((data[3] << 8) | data[2]);
	*z = (int16_t)((data[5] << 8) | data[4]);
// lacze wartosci MSB i LSB w jedna 16 bitowa liczbe
// zeby to zrobic trzeba zrobic w MSB miejsce na mlodsza czesc liczby
// XXXXXXXX << 8 = XXXXXXXX00000000
// w przypadku ADXL345 najpierw jest mlodszy bajt pozniej starszy
}
