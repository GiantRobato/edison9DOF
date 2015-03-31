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
	int file;

	//Using i2c-1 since that is what it is connected to on the Edison
	if((file = open(I2C_DEV_NAME, O_RDWR)) < 0){
		//This is for error handling
		printf("Failed to open the i2c bus");
		return 1;
	}

	//DEBUG
	printf("Successfully opened the i2c bus!\n");

	//TODO: Move the following into a function called write_bytes
	//Create data for storing the return values from reading the registers
	uint8_t xm_id;

	//need to use this struct for ioctl
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages [2];

	//add bit for multibyte read
	uint8_t reg = WHO_AM_I_XM;

	//set data for i2c message
	messages[0].addr 	= XM_ADDRESS;
	messages[0].flags 	= 0; //write
	messages[0].len		= 1; //sending only 1 byte
	messages[0].buf		= &reg; //pointer to msg data we want to send
								//in this case it is specifiying the 
								//register we want to read from i.e.
								// the who_am_i_reg

	//read from i2c
	messages[1].addr 	= XM_ADDRESS;
	messages[1].flags 	= I2C_M_RD; //read
	messages[1].len		= 1; //sending only 1 byte
	messages[1].buf		= &xm_id; //pointer to msg data, e.g. pointer to
									//where we want to store the output of the
									//call

	//convert to proper i2c packet for sending
	packets.msgs	= messages;
	packets.nmsgs	= 2;

	//Send the message and recieve!
	//Note how we use the the "file" variable when we do any ioctl call.
	//We are setting the I2C_RDWR since we are doing both with our call.
	//Also we are passing in a pointer to our packets.
	ioctl(file, I2C_RDWR, &packets);


	printf("accel & mag id: %02x\n", xm_id);
	if(xm_id != 0x49){
		printf("accel & mag id does not match!\n");
	} else {
		printf("accel & mag id matches!! \n");
	}


	uint8_t gyro_id;

	//
	reg = WHO_AM_I_G;

	//Do the same thing for gyro
	//set data for i2c message
	messages[0].addr 	= G_ADDRESS;
	messages[0].flags 	= 0; //write
	messages[0].len		= 1; //sending only 1 byte
	messages[0].buf		= &reg; //pointer to msg data we want to send

	//read from i2c
	messages[1].addr 	= G_ADDRESS;
	messages[1].flags 	= I2C_M_RD; //read
	messages[1].len		= 1; //sending only 1 byte
	messages[1].buf		= &gyro_id; //pointer to msg data, e.g. pointer to
									//where we want to store the output of the
									//call

	//convert to proper i2c packet for sending
	packets.msgs	= messages;
	packets.nmsgs	= 2;

	//Send the message and recieve!
	//Note how we use the the "file" variable when we do any ioctl call.
	//We are setting the I2C_RDWR since we are doing both with our call.
	//Also we are passing in a pointer to our packets.
	ioctl(file, I2C_RDWR, &packets);


	printf("gyro id: %02x\n", gyro_id);
	if(gyro_id != 0xD4){
		printf("gyro id does not match!\n");
	} else {
		printf("gyro id matches!! \n");
	}	

	return 0;
}
