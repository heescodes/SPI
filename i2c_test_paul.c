#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "i2c-paul.h" //[paul] have to make   


int main() {
    int fd;
    int ret;
    char *dir_dev = "/dev/i2c-1";
    int addr = 0x3c;  // Slave address
    const char buf_on[4] = {0x00, 0xAF, 0x00, 0xA5};  // On Test
    const char buf_off[2] = {0x00, 0xAE};  // OFF Test 
/*  |   buf[0]   |  buf[1] |                                                        
    |Control byte|Data byte|  
*/
//buf[0]=0x00 : Following Data byte is a command
//buf[0]=0x40 : Following Data byte is data to be stor    ed in GDDRAM (ex)Fill     
    printf("----------File Open Start---------\n");
    // I2C Adapter Device Open
    if ((fd = open(dir_dev, O_RDWR)) < 0) {
        perror("Failed to open the i2c-adapter file\n");
        return -1;
    }

    if( (ret = paul_i2c_write_2byte(fd,addr,buf_on)) < 0 ){
        perror("Failed to write to i2c device\n"); 
        return -1;    
    }

    if(close(fd)<0){
        perror("Failed to close the i2c-adapter file\n");
        return -1;
    }

    printf("Data successfully written to i2c device.\n"); 
    return 0;
}
    
