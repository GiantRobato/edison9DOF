#ifndef __INTEL_EDISON_9DOF_IMU_I2C_H__
#define __INTEL_EDISON_9DOF_IMU_I2C_H__

#include <stdint.h>

//The i2c bus being used
#define I2C_DEV_NAME		"/dev/i2c-1"

//The i2c device addresses
#define G_ADDRESS			0x6b
#define XM_ADDRESS			0x1d

//Adress registers
#define WHO_AM_I_XM			0x0F 
#define WHO_AM_I_G			0x0F

//lets us read numerous bytes
#define ENABLE_MULTI_BYTE_READ 0x80


#define DEBUG

//used to enable numerous debug print statements
#ifdef 	DEBUG
#define DEBUG_FLAG 1
#else
#define DEBUG_FLAG 0
#endif


int DMOpenDevFile();
int DMReadI2CMessages(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData, uint8_t count);
int DMReadI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData);
int DMWriteI2CMessages(int devFile, uint8_t i2cAddress, uint8_t *writeData, uint8_t count);
int DMWriteI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t writeData);
int DMPingSensors(int devFile);

#endif
