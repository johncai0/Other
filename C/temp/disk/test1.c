#include <stdio.h>
#include <sys/statfs.h>
struct aaa { 
	int a;
	int b;
	}ccc;
main()
{
struct statfs diskInfo;
statfs("/",&diskInfo);
printf("bsize: %ld\tblocks: %ld\n",diskInfo.f_bsize, diskInfo.f_blocks);
struct ccc bbb;
bbb.a = 5;
bbb.b = 7;
printf("%d %d\n", bbb.b, bbb.a);	
printf("%d %d\n", &bbb->b, &bbb->a);	
//struct statfs *disk;
//statfs("/",disk);
//printf("bsize: %ld\tblocks: %ld\n",disk->f_bsize, disk->f_blocks);
}
