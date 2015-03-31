#include <stdio.h>
#include "../include/intel-edison-9dof-imu-i2c.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <fcntl.h>

//TODO: Move the following defines into .h

int main(int argc, char* argv[]){

	printf("Opening the i2c sensor device!\n\n");

	//Here we are opening the bus
	int devFile = DMOpenDevFile();

	//Using i2c-1 since that is what it is connected to on the Edison
	if(devFile < 0){
		printf("Failed to open the i2c bus");
		return 1;
	}

	//TODO: Move the following into a function called write_bytes
	//Create data for storing the return values from reading the registers
	uint8_t xm_id;

	//This will write to xm_id the output from reading the WHO_AM_I_XM register
	DMReadI2CMessage(devFile, XM_ADDRESS, WHO_AM_I_XM, &xm_id);

	printf("accel & mag id: %02x\n", xm_id);
	if(xm_id != 0x49){
		printf("accel & mag id does not match!\n");
	} else {
		printf("accel & mag id matches!! \n");
	}


	uint8_t gyro_id;

	//This will write to gyro_id the output from reading the WHO_AM_I_G register
	DMReadI2CMessage(devFile, G_ADDRESS, WHO_AM_I_G, &gyro_id);

	printf("gyro id: %02x\n", gyro_id);
	if(gyro_id != 0xD4){
		printf("gyro id does not match!\n");
	} else {
		printf("gyro id matches!! \n");
	}	

	return 0;
}
