#include <stdio.h>
#include "../include/intel-edison-9dof-imu-i2c.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

//TODO: Move the following defines into .h

//The i2c bus being used
#define I2C_DEV_NAME		"/dev/i2c-1"

//The i2c device addresses
//[]Comment how these addresses were found
#define G_ADDRESS			0x1D
#define XM_ADDRESS			0x6B

//Adress registers
//[] Comment why these register addresses are the same
#define WHO_AM_I_XM			0x0F 
#define WHO_AM_I_G			0x0F

int main(int argc, char* argv[]){

	printf("Opening the i2c sensor device!\n\n");

	//Here we are opening the bus
	int file;

	//Using i2c-1 since that is what it is connected to on the Edison
	char * filename = "/dev/i2c-1";
	
	if((file = open(filename, O_RDWR)) < 0){
		//This is for error handling
		printf("Failed to open the i2c bus");
		return 1;
	}

	//DEBUG
	printf("Successfully opened the i2c bus!\n");

	//TODO: Move the following into a function called write_bytes
	//Create data for storing the return values from reading the registers
	uint8_t gyro_id;

	//need to use this struct for ioctl
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages [2];

	//add bit for multibyte read
	uint8_t reg = WHO_AM_I_G | 0x80;

	//set data for i2c message
	messages[0].addr 	= G_ADDRESS;
	messages[0].flgas 	= 0; //write
	messages[0].len		= 1; //sending only 1 byte
	messages[0].buf		= &reg; //pointer to msg data we want to send
								//in this case it is specifiying the 
								//register we want to read from i.e.
								// the who_am_i_reg

	//read from i2c
	messages[0].addr 	= G_ADDRESS;
	messages[0].flgas 	= I2C_M_RD; //read
	messages[0].len		= 1; //sending only 1 byte
	messages[0].buf		= &gyro_id; //pointer to msg data, e.g. pointer to
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

	printf("Recieved back this message: %02x\n", gyro_id);


	return 0;
}
