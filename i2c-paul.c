/*
struct i2c_rdwr_ioctl_data{
    struct i2c_msg __user *msgs;
    __u32 nmsgs;
};
*/

//int i2c_write_byte(int fd);
#include <linux/i2c.h>
#include <linux/i2c-dev.h>  
#include "i2c-paul.h"

int ioctl_data_transfer(int fd,struct i2c_msg *msgs, u32 msg_cnt){                                       
                                                                                
    struct i2c_rdwr_ioctl_data ioctl_data;                                      
                                                                                
    ioctl_data.msgs     = msgs;                                                 
    ioctl_data.nmsgs    = msg_cnt;                                              
                                                                                
    if(ioctl(fd,I2C_RDWR,&ioctl_data)<0) return -1;                             
                                                                                
    return 0;                                                                   
}       

u32 set_i2c_msg(struct i2c_msg *pmsg, u16 addr, u16 rw, u8 *rwbuf)
{
    u32 msg_cnt=0;
    if(rwbuf != NULL){
        pmsg->addr = addr;
        pmsg->flags = rw; //1:read, 0:write
        pmsg->len = sizeof(*rwbuf);
        pmsg->buf = rwbuf;
        msg_cnt++;
    }
    //else return -1;

    return msg_cnt;
}

int paul_i2c_write_2byte(int fd, u16 addr, unsigned char *buf){
    struct i2c_msg msgs[2];
    u32 nmsgs;    
    struct i2c_msg* pmsg = msgs;
    //int ret;

    nmsgs=set_i2c_msg(pmsg,addr,0,buf); // transfer에 set_i2c_msg를 넣자
    return ioctl_data_transfer(fd,pmsg,0); 
}
