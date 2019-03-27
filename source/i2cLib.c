
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "i2cLib.h"
#define I2C_DEVICE_ADDRESS 0x50
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"
int initI2cBus(char* bus, int address)
{
    int i2cFileDesc = open(bus, O_RDWR);
    if (i2cFileDesc < 0) {
    printf("I2C: Unable to open bus for read/write (%s)\n",bus);
    perror("Error is:");
    exit(1);
    }
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
    if (result < 0) {
    perror("I2C: Unable to set I2C device to slaveaddress.");
    exit(1);
    }
    return i2cFileDesc;
}


unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr)
{
 // To read a register, must first write the address
 int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
 if (res != sizeof(regAddr)) {
 perror("Unable to write i2c register.");
 exit(-1);
 }
 // Now read the value and return it
 char value = 0;
 res = read(i2cFileDesc, &value, sizeof(value));
 if (res != sizeof(value)) {
 perror("Unable to read i2c register");
 exit(-1);
 }
 return value;
}