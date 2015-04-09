#include "../include/intel-edison-9dof-imu-i2c.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

/**
	Attempts to open the the device file for the i2c-1 bus

	@return devFile which gives us a file handler for future ioctl calls
**/

int DMOpenDevFile(){
	int devFile;
	if((devFile = open(I2C_DEV_NAME, O_RDWR)) < 0){
		//Could not open i2c bus
		return -1;
	}
	return devFile;
}

/**
	Sends multiple I2C messages 

    @param devFile is the device file which is return from open("file", <flags>)
    @param i2cAddress is the I2C address from the i2c-1 bus specifying which sensor
    @param regAddress is the register address we are interested in on the sensor we specified
    @return the output of the i2c call
*/
int DMReadI2CMessages(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData, uint8_t count){
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages [2];

	regAddress = regAddress | ENABLE_MULTI_BYTE_READ;

	//specify to imu sensor which register we want to read from
	messages[0].addr 	= i2cAddress;
	messages[0].flags 	= 0;			//write
	messages[0].len		= 1; 			//sending only 1 byte
	messages[0].buf		= &regAddress;	//pointer to msg data we want to send



	//read from register we specified
	messages[1].addr 	= i2cAddress;
	messages[1].flags 	= I2C_M_RD; 	//read
	messages[1].len		= count; 		//sending specified num of bytes
	messages[1].buf		= returnData;	//write to returnData

	//convert to proper i2c packet for sending
	packets.msgs	= messages;
	packets.nmsgs	= 2;

	//Send i2c message to request for data from sensor
	return ioctl(devFile, I2C_RDWR, &packets);
}

/**
	Calls DMReadI2CMessages with count = 1, generally used to read a single
	byte like the WHO_AM_I registers

	(see DMReadI2CMessages for paramter descriptions)
**/
int DMReadI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData){
	return DMReadI2CMessages(devFile, i2cAddress, regAddress, 
returnData, 1);
}

/**
	This pings the sensors and returns a flag if it was successful or not. Note
	that if DEBUG is on then it will give a print out to the console.

	@param devFile the device file handler from open("file", <flags>)
	@return 0 if successful, -1 if error
**/
int DMPingSensors(int devFile){
	uint8_t xm_id, gyro_id;

	DMReadI2CMessage(devFile, XM_ADDRESS, WHO_AM_I_XM, &xm_id);
	DMReadI2CMessage(devFile, G_ADDRESS, WHO_AM_I_G, &gyro_id);

	if(DEBUG_FLAG){
		printf("gyro_id returned was: %X\n", gyro_id);
		printf("xm_id returned was: %X\n", xm_id);
	}

	if(xm_id != 0x49 || gyro_id != 0xD4){
		return -1;
	}
	return 0;
}

int DMWriteI2CMessages(int devFile, uint8_t i2cAddress, uint8_t *writeData, uint8_t count){
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages [1];

	messages[0].addr 	= i2cAddress;
	messages[0].flags 	= 0; 			//write
	messages[0].len		= count; 		//sending specified num of bytes
	messages[0].buf		= writeData;	//data to send to sensor

	packets.msgs 		= messages;
	packets.nmsgs 		= 1;

	return ioctl(devFile, I2C_RDWR, &packets) >= 0;
}

int DMWriteI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t writeData){
	uint8_t buffer[2];

	buffer[0] = regAddress;
	buffer[1] = writeData;
	return DMWriteI2CMessages(devFile, i2cAddress, buffer, 2);
}
