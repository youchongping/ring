#ifndef __RING_H_
#define __RING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
	RING_GETS_FAILED = -6,
	RING_PUTS_FAILED = -5,
    RING_GET_FAILED = -4,
    RING_PUT_FAILED = -3,
    RING_RESET_FAILED = -2,
    RING_CREATE_FAILED = -1,
    RING_SCUCESS = 0,
};
//ring  structure
typedef struct 
{
    int size;//the size of ring's effective capacity
    unsigned char* ptr_o;//origin address
    unsigned char* ptr_r;//next read address 
    unsigned char* ptr_w;//next write address 
    int count;//effective data count in ring now
}RB;
/**********funtions always use*************/
int ring_create(RB* r,char* buf,int size);
int ring_putchar(RB* r,unsigned char c);
int ring_getchar(RB* r,unsigned char* c);
int ring_puts(RB* r,unsigned char*buf,int buf_len);
int ring_gets(RB* r,unsigned char* buf,int len_tryto_read,int* len_actual_read);
/**********funtions may need*************/
int ring_reset(RB*r);
int ring_get_count(RB*r);
int ring_get_remain(RB* r);
int ring_is_empty(RB* r);
int ring_is_full(RB* r);
int ring_perror(char* fmt,int error);
#endif
