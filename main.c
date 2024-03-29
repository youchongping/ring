#include "ring.h"
#include <unistd.h>

#define BUFF_SIZE 256
unsigned char* buf;
RB r;

int main()
{
	buf = (unsigned char*)malloc(BUFF_SIZE);
	//RB r;
	int ret;
	int len;

	ret = ring_create(&r,buf,BUFF_SIZE);
	if(ret<0)
	{
		ring_perror("ring_create()",ret);
	}

	unsigned char out[11];
	unsigned char in[11];
	memset(out,0,sizeof(out));
	memset(in,0,sizeof(in));
	memcpy(in,"abcdef1234",strlen("abcdef1234"));

	//in  generic application ,when the ring is full , should gets() out some data before puts()
	while(1)
	{
		
		ret = ring_puts(&r,in,strlen(in));
		if(ret != RING_SCUCESS)
		{
			ring_perror("ring_puts() ",ret);
		}
		printf("1....ring_puts,r.count %d remain:%d ............1\n",r.count,ring_get_remain(&r));
		printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
		memset(out,0,sizeof(out));
		ret = ring_gets(&r,out,sizeof(out)-1,&len);
		if(ret != RING_SCUCESS)
		{
			ring_perror("ring_gets() ",ret);
		}

		printf("2....ring_gets  %d:%s r.count %d remain:%d............2\n",len,out,r.count,ring_get_remain(&r));
		printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
		
		sleep(1);

	}
	free(buf);
	return 0;
}
