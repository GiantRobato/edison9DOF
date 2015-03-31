#include "../include/intel-edison-9dof-imu-i2c.h"
#include <fcntl.h>

int DMOpenDevFile(){
	int file;
	if((file = open(I2C_DEV_NAME, O_RDWR)) < 0){
		//Could not open i2c bus
		return -1;
	}
	return file;
}

int DMReadI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData, uint8_t count){
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages [2];

	//specify to imu sensor which register we want to read from
	messages[0].addr 	= i2cAddress;
	messages[0].flags 	= 0;			//write
	messages[0].len		= 1; 			//sending only 1 byte
	messages[0].buf		= &regAddress;	//pointer to msg data we want to send

	//read from register we specified
	messages[1].addr 	= i2cAddress;
	messages[1].flags 	= I2C_M_RD; 	//read
	messages[1].len		= 1; 			//sending only 1 byte
	messages[1].buf		= returnData;	//write to returnData

	//convert to proper i2c packet for sending
	packets.msgs	= messages;
	packets.nmsgs	= 2;

	//Send i2c message to request for data from sensor
	return ioctl(devFile, I2C_RDWR, &packets);
}

int DMReadI2CMessage(int devFile, uint8_t i2cAddress, uint8_t regAddress, uint8_t *returnData){
	return DMReadI2CMessage(devFile, i2cAddress, regAddress, returnData, 1);
}
