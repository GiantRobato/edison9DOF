#ifndef __INTEL_EDISON_9DOF_IMU_I2C_H__
#define __INTEL_EDISON_9DOF_IMU_I2C_H__

//The i2c bus being used
#define I2C_DEV_NAME		"/dev/i2c-1"

//The i2c device addresses
#define G_ADDRESS			0x6b
#define XM_ADDRESS			0x1d

//Adress registers
#define WHO_AM_I_XM			0x0F 
#define WHO_AM_I_G			0x0F

int DMOpenDevFile();

#endif
