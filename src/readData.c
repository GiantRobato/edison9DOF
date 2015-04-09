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

	if(DMPingSensors(devFile) < 0){
		if(DEBUG_FLAG){
			printf("Could not ping sensors");
		}
		return 1;
	}	

	//store i2c messages
	uint8_t data[6] = {0};

	//hex address for acceleration measurements
	uint8_t accelReg = 0x28;

	//temporary storage variables
	int16_t x_raw;
	int16_t y_raw;
	int16_t z_raw;

	//normal mode, all axes
	//write_byte(file, G_ADDRESS, CTRL_REG1_G, 0x0F);

	//uint8_t reg4_g;
	//zero the scale bits, then set them
	//readbyte  (file, G_ADDRESS, CTRL_REG4_G, &reg4_g);
	//write_byte(file, G_ADDRESS, CTRL_REG4_G, (reg4_g & 0xCF) | scale
	//	<< 4);


	//read from gyro
	DMReadI2CMessages(devFile, XM_ADDRESS, accelReg, &data[0], 6);

	//parse message data back into 16 bits
	x_raw = ((data[1] << 8) | data[0]);
	y_raw = ((data[3] << 8) | data[2]);
	z_raw = ((data[5] << 8) | data[4]);

	//print out reading
	printf("read values: x = %d\ty = %d\tz = %d\n", x_raw, y_raw, z_raw);
	
	return 0;
}
