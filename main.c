#include "ring.h"


#define BUFF_SIZE 5
int main()
{
	unsigned char buf[BUFF_SIZE]={0};
	RB r;
	int ret;
	unsigned char c;
	ret = ring_create(&r,buf,sizeof(buf));
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_create()",ret);
		return 1;
	}
	/**********putchar getchar***********/
	ret = ring_putchar(&r,'g');
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_putchar",ret);
		return 1;
	}

	ret = ring_getchar(&r,&c);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_getchar",ret);
		return 1;
	}
	printf("ring_getchar:%c \n",c);
	/**********puts gets***********/
	char in[]="china";
	printf("ring_gets:%s \n",in);
	ret = ring_puts(&r,in,strlen(in));
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_puts",ret);
		return 1;
	}
	
	char out[10]={0};
	int len;
	ret = ring_gets(&r,out,r.size,&len);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_gets",ret);
		return 1;
	}

	printf("ring_gets %d:%s \n",len,out);
	
	return 0;
}
