#include <stdio.h>
#include "../include/intel-edison-9dof-imu-i2c.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

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

	return 0;
}
