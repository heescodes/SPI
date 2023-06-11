#include <linux/i2c.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

int ioctl_data_transfer(int fd,struct i2c_msg *msgs, u32 msg_cnt); 
int set_i2c_msg(struct i2c_msg *pmsg, u16 addr, u16 rw, u8 *rwbuf);
int paul_i2c_write_2byte(int fd, u16 addr, const char *buf);
