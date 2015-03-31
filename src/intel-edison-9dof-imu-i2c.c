#include "../include/intel-edison-9dof-imu-i2c.h"

int DMopenDevFile(){
	int file;
	if((file = open(I2C_DEV_NAME, O_RDWR)) < 0){
		//Could not open i2c bus
		return -1;
	}
	return file;
}