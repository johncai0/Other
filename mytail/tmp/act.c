#include <stdio.h>
#define MAXLEN	1024
int getlen(char *a)
{
	FILE *fp;
	char buf[MAXLEN];
	int i=0;
	if ((fp = fopen(a,"r")) == NULL) {
		printf("Open %s ERROR!\n",a);
		return -1;
	}
	fseek(fp,119,SEEK_SET);
	while (fgets(buf,MAXLEN,fp) != NULL) {
		printf("LENG:[%d] sleek:[%ld] %s",++i, ftell(fp),buf);
	}
	return i;
}

int main(void) 
{
	int i=getlen("./test.c");
	return i;
}
