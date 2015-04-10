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

	DMInitAccel(devFile);

	struct Triplet rawData;

	DMReadAccelRawTriplet(devFile, &rawData);


	//print out reading
	printf("read values: x = %d\ty = %d\tz = %d\n", rawData.x, rawData.y, rawData.z);
	
	return 0;
}
