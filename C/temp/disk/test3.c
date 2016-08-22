#include <stdio.h>
#include <sys/statfs.h>
struct dskstat {
        char name[16];
        char mntp[64];
        double inodeuse;
        double usespace;
};
int get_dsk(struct dskstat dskst[31])
{
        FILE *fp;
        char buf[512],*tmstr = "/dev/",*str1p,*str2p,*temp;
        int i,y=0;
        //struct dskstat sdkst[31];
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
                        sdkst[y].inodeuse = 100 - ((double)stat.f_ffree / (double)stat.f_files * 100);
                        sdkst[y].usespace = 100 - ((double)stat.f_bfree / (double)stat.f_blocks * 100);
                        y++;
                }
        }
        return y;
}
main()
{
	struct dskstat test[31];
	int i = get_dsk(test);
	printf("%s %s %0.2f %0.2f\n",test[1].name,test[1].mntp, test[1].usespace,test[1].inodeuse);
}
