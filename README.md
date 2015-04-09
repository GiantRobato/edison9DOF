# edison9DOF
A little demo on using the edison 9 DOF board

## How to Use
Download with
```
git clone https://github.com/penguindustin/edison9DOF
```
The compile and run with
```
make clean all
```
This generates the readData executable in the bin/ folder.

Runing the program should output something like this:
```
./bin/readData

//OUTPUT
Opening the i2c sensor device!

gyro_id returned was: D4
xm_id returned was: 49
read values: x = 5600   y = -12072      z = -73
```
## Wiki (in Development)
See the Wiki! I talk about how the code works and why values are set the way are.

## Future features
 - [ ] simple API to intialize, update settings, and read data
 - [ ] example files and calibration executables

##Copyright and License
Code and documentation released under the MIT license
