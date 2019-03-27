#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <main.h>
#define READING_ADDRESS 0xA0
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"
#define I2C_DEVICE_ADDRESS 0x50
// Put the above functions Here
int main(void)
{
    //Initialize file
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS2,I2C_DEVICE_ADDRESS);
    //Read the register
    int currBPM = readI2cReg(i2cFileDesc, READING_ADDRESS);
    printf("Current BPM : %d\n", currBPM);
    close(i2cFileDesc);
    return 0;
}