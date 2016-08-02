#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
main()
{
	MD5_CTX ctx;
	unsigned char outmd[16];
	int i;
	memset(outmd,'\0', 16);
	MD5_Init(&ctx);
	MD5_Update(&ctx,"john",strlen("john"));
	MD5_Final(outmd,&ctx);
	for (i=0; i<16; i++)
	{
		printf("%02x",outmd[i]);
	}
	printf("\n");
}
