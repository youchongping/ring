#include "ring.h"


#define BUFF_SIZE 5
unsigned char* buf;
RB r;

int main()
{
	buf = (unsigned char*)malloc(BUFF_SIZE);
	//RB r;
	int ret;
	unsigned char c;
	ret = ring_create(&r,buf,BUFF_SIZE);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_create()  ",ret);
		return 1;
	}
	/**********putchar getchar***********/
	ret = ring_putchar(&r,'g');
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_putchar() ",ret);
		return 1;
	}
	printf("1....ring_putchar,r.count %d ............1\n",r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	ret = ring_getchar(&r,&c);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_getchar() ",ret);
		return 1;
	}
	printf("2....ring_getchar:%c,r.count %d ............2\n",c,r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	
	/**********puts gets***********/
	ring_reset(&r);
	char in[]="1234";
	ret = ring_puts(&r,in,strlen(in));
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_puts() ",ret);
	}
	printf("3....ring_puts,r.count %d ............3\n",r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	char out[20]={0};
	int len;
	ret = ring_gets(&r,out,sizeof(out)-1,&len);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_gets() ",ret);
	}

	printf("4....ring_gets  %d:%s r.count %d ............4\n",len,out,r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	
	memset(out,0,sizeof(out));
	ret = ring_gets(&r,out,sizeof(out)-1,&len);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_gets() ",ret);
	}

	printf("5....ring_gets  %d:%s r.count %d ............5\n",len,out,r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	/******puts gets again*******/
	memcpy(in,"abcd",strlen("abcd"));
	ret = ring_puts(&r,in,strlen(in));
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_puts() ",ret);
	}
	printf("6....ring_puts,r.count %d volume:%d ............6\n",r.count,ring_get_remain(&r));
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	memset(out,0,sizeof(out));
	ret = ring_gets(&r,out,sizeof(out)-1,&len);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_gets() ",ret);
	}

	printf("7....ring_gets  %d:%s r.count %d ............7\n",len,out,r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	
	memset(out,0,sizeof(out));
	ret = ring_gets(&r,out,sizeof(out)-1,&len);
	if(ret != RING_SCUCESS)
	{
		ring_perror("ring_gets() ",ret);
	}

	printf("8....ring_gets  %d:%s r.count %d ............8\n",len,out,r.count);
	printf("w:%ld r:%ld\n",(r.ptr_w-r.ptr_o),(r.ptr_r-r.ptr_o));
	free(buf);
	return 0;
}
