#ifndef __INTEL_EDISON_9DOF_IMU_I2C_H__
#define __INTEL_EDISON_9DOF_IMU_I2C_H__

#include <stdint.h>

/******************
|   I2C Defines   |
******************/

//The i2c bus being used
#define I2C_DEV_NAME		"/dev/i2c-1"

//The i2c device addresses
#define G_ADDRESS			0x6B
#define XM_ADDRESS			0x1D

/************************
|   CONTROL Registers   |
************************/

//Adress registers
#define WHO_AM_I_XM			0x0F 
#define WHO_AM_I_G			0x0F

//The register address for the output buffer
#define GYRO_OUT_X_G 		0x28

//Sensor Control registers
#define CTRL_REG1_G 		0x20 	//register used to enable and turn on/off

//Byte data to enable Gyroscope in normal mode + enable x, y, z sensors
#define EN_G_NM_XYZ 		0x0F

/*******************
|   UTIL Defines   |
*******************/

//lets us read numerous bytes
#define ENABLE_MULTI_BYTE_READ 0x80

#define DEBUG

//used to enable numerous debug print statements
#ifdef 	DEBUG
#define DEBUG_FLAG 1
#else
#define DEBUG_FLAG 0
#endif

struct Triplet{
	int16_t x,
	int16_t y,
	int16_t z;
};


int DMOpenDevFile();
int DMReadI2CMessages(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData, uint8_t count);
int DMReadI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData);
int DMWriteI2CMessages(int devFile, uint8_t i2cAddress, uint8_t *writeData, uint8_t count);
int DMWriteI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t writeData);
int DMPingSensors(int devFile);
int DMInitGyro(int devFile);
int DMReadGyroRaw(int devFile, uint8_t *returnData);

#endif
