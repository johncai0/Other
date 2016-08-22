#include <stdio.h>
#include <sys/statfs.h>
struct dskstat {
        char name[16];
        char mntp[64];
        double inodeuse;
        double usespace;
};
main()
{
	FILE *fp;
	char buf[512],*tmstr = "/dev/",*str1p,*str2p,*temp;
	int i,y=0;
	struct dskstat sdkst[31];
	struct statfs stat;
	if((fp=fopen("/etc/mtab","r")) == NULL) {
		fprintf(stderr,"ERROR: Open mtab ERROR!\n");
		return -9;
	}
	while (fgets(buf, sizeof(buf),fp) != NULL) {
		for (str1p = tmstr,str2p = buf,i = 0; *str1p == *str2p; str1p++,str2p++,i++)
			;
		if (i == 5) {
			sscanf(buf,"%s %s %s",&(sdkst[y].name),&(sdkst[y].mntp), &temp);
			statfs(sdkst[y].mntp, &stat);
			//printf("%s\t%s: use(%0.2f%) inode_use(%0.2f%)\n", sdkst[y].mntp, sdkst[y].name, 100 - ((double)stat.f_bfree 
			//	/ (double)stat.f_blocks * 100), 100 - ((double)stat.f_ffree / (double)stat.f_files * 100));
			sdkst[y].inodeuse = 100 - ((double)stat.f_ffree / (double)stat.f_files * 100);
			sdkst[y].usespace = 100 - ((double)stat.f_bfree / (double)stat.f_blocks * 100);
			y++;
		}
	}
	printf("DEV\t\tMNT\tSPACE_USE\tINODE_USE\n");
	for (i = 0; i < y; i++)
		printf("%s:\t%s\tuse: (%2.0f%)\tinode_use: (%2.0f%)\n",sdkst[i].name,
				sdkst[i].mntp,sdkst[i].usespace,sdkst[i].inodeuse);
	return 0;
}
