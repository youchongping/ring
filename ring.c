#include "ring.h"

int ring_create(RB* r,char* buf,int size)
{
    if(buf == NULL)return RING_CREATE_FAILED;
    r->ptr_o = buf;
    r->ptr_w = buf;
    r->ptr_r = buf;
    r->size  = size;
    r->count = 0;
    return RING_SCUCESS;
}

int ring_putchar(RB* r,unsigned char c)
{
    if(ring_is_full(r)) return RING_PUT_FAILED;
    
	*(r->ptr_w) = c;
    if(r->ptr_w == (r->ptr_o + r->size-1))//at the top , jump to the origin address
    {
        r->ptr_w = r->ptr_o;
    }
    else
    {
        (r->ptr_w)++;
    }
    
    (r->count)++;
    return RING_SCUCESS;
}

int ring_getchar(RB* r,unsigned char* c)
{
    if(ring_is_empty(r))return RING_GET_FAILED;

    *c = *(r->ptr_r);
    r->count--;

    if(r->ptr_r == (r->ptr_o + r->size-1))
    {

        r->ptr_r = r->ptr_o;
    }
    else
    {
        (r->ptr_r)++;
    }
    return RING_SCUCESS;
}

int ring_puts(RB* r,unsigned char*buf,int buf_len)
{
	int volume;
	volume = ring_get_remain(r);
	if(volume <buf_len)return RING_PUTS_FAILED;
	while(buf_len)
	{
		if(ring_putchar(r,*buf)<0)
		{
			ring_perror("ring_putchar() ",RING_PUT_FAILED);
			return RING_PUTS_FAILED;
		}
		buf++;
		buf_len--;

	}
	return RING_SCUCESS;
}

int ring_gets(RB* r,unsigned char* buf,int len_tryto_read,int* len_actual_read)
{
	*len_actual_read =0;
	while(*len_actual_read <len_tryto_read)
	{
		if(ring_getchar(r,buf)<0)
		{
			ring_perror("ring_getchar() ",RING_GET_FAILED);
			return RING_GETS_FAILED;
		}
		(*len_actual_read)++;
		buf++;
	}
	
	return RING_SCUCESS;
}
/**********other may need functions**************/
int ring_reset(RB*r)
{
    if(r->ptr_o == NULL)
    {
        printf("[error]need create ring first \n");
        return RING_RESET_FAILED;
    }

    r->ptr_w = r->ptr_o;
    r->ptr_r = r->ptr_o;
    r->count = 0;
    return RING_SCUCESS;
}
int ring_get_count(RB*r)
{
    return r->count;
}

int ring_get_remain(RB* r)
{
    return ((r->size)-(r->count));
}
int ring_is_empty(RB* r)
{
    return (r->count == 0)? 1:0;
}

int ring_is_full(RB* r)
{
    return (r->count >= r->size) ? 1:0;
}

int ring_perror(char* fmt,int error)
{
	char* str = (char*)malloc(128);
	memset(str,0,128);
	strcat(str,fmt);

	switch(error)
	{
		case RING_GETS_FAILED:
				strcat(str," [warning]  no so much data");
				break;
		case RING_PUTS_FAILED:
				strcat(str,"RING_PUTS_FAILED");
				break;
		case RING_GET_FAILED:
				strcat(str," [warning]  ring empty");
				break;
		case RING_PUT_FAILED:
				strcat(str,"RING_GETCHAR_FAILED");
				break;
		case RING_RESET_FAILED:
				strcat(str,"RING_RESET_FAILED");
				break;
		case RING_CREATE_FAILED:
				strcat(str,"RING_CREATE_FAILED");
				break;
		case RING_SCUCESS:
				strcat(str,"RING_SCUCESS");
				break;
		default:
				strcat(str,"unknow error value");
				break;
	}
	fprintf(stdout,"%s \n",str);
	return 0;
	
}































