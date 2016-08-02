#include "mon.h"
int getsize(struct diskvar *a)
{
	struct statfs buf;
	if (statfs(a->path,&buf)) {
		return errno;
	}
	a->bts=buf.f_blocks;
	a->bfs=buf.f_bfree;
	a->its=buf.f_files;
	a->ifs=buf.f_ffree;
	return 0;
}
int getdisk(void)
{
	FILE *fp=NULL;
	char line[MAXLINE];
	char *file="/etc/mtab";
	int i;
	struct diskvar disk[MAXDSK];
	char mpt[4096],dev[1024];
	if ((fp = fopen(file,"r")) == NULL) {
		fprintf(stderr,"[getdisk]->[open]:: ERRNO: [%s]  CASE: %s\n",file,strerror(errno));
		return -1;
	}
	for (i=0;fgets(line,MAXLINE, fp) != NULL && i < MAXDSK; i++) {
		if (equs("/dev/",line)) {
			sscanf(line,"%s %s ", dev,mpt);
			strcpy(disk[i].path,mpt);
			strcpy(disk[i].dev,dev);
			if (getsize(&(disk[i]))) {
				fprintf(stderr,"[getdisk]->[getsize]->[statfs]:: ERRNO: [%s]  CASE: %s\n",
					disk[i].path,strerror(errno));
				return -1;
			}
			fprintf(stdout,"mount: [%s] dev: [%s] %ld %ld %ld %ld\n", 
				disk[i].path,disk[i].dev,disk[i].bts,disk[i].bfs,disk[i].its,disk[i].ifs);
		}
	}
	return 0;
}

int main(void)
{
	return getdisk();
}
