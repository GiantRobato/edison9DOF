# Changelog

## Unreleased
 * Triplet Data structure for storing sensor data
 * Triplet float data structure for storing converted sensor data
 * Converting raw sensor data into scaled unit data
 * Function(s) to initialize sensors
 * Function(s) to set Full Scale Values
 * Implement in OO flaver (possibly future github project)

## 0.1.2 - 2015-04-10
### Added
 * added Triplet Data structure
 * added DMReadGyroRaw()
 * added DMReadGyroTriplet()
 * added DMInitAccel()
 * added DMReadAccelRaw()
 * added DMReadAccelTriplet()
 * added DMInitMag()
 * added DMReadMagRaw()
 * added DMReadMagTriplet()
### Changed
 * functionality to use Triplets versus multiple ints

## 0.1.1 - 2015-04-08
### Added
 * added function comments
 * added I2C functions to read and write data
 * added function to open up I2C bus
 * added function to ping sensors for sanity check
### Changed
 * Moved #defines from testing gyro data to intel-edison-9dof.h
### Fixed
 * fixed errors, compiles correctly