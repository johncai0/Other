#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
int strstart(const char *src,const char *des) {
        if (strstr(src,des) == src && strlen(src) == strlen(des))
                return 0;
        return 1;
}
int scdirect(char *path) {
	DIR *dir;
        struct dirent *ptr;
        char buf[4096]={0};
        if ((dir = opendir(path)) == NULL) {
		fprintf(stderr,"fscan.opendir[ERROR]: [%s]%s!\n",path,strerror(errno));
                return -1;
	}
        while ((ptr  = readdir(dir)) != NULL) {
                if (strstart(ptr->d_name,".")&strstart(ptr->d_name,"..")) {
                                sprintf(buf,"%s/%s",path,ptr->d_name);
                                prtf(buf);
                }
        }
        closedir(dir);
}
int prtf(char *path) {
	struct stat fst;
	if (stat(path,&fst) == -1) {
		fprintf(stderr,"fscan.stat[ERROR]: [%s]%s!\n",path,strerror(errno));
		return -1;
	}
	if (S_ISDIR(fst.st_mode)) {
		fprintf(stdout,"%s\n",path);
		scdirect(path);
	} else 
		fprintf(stdout,"%s\n",path);
	return 0;
}

int main(int argc, char **argv) {
	char path[2096]={0};
	if (argc < 2)
		sprintf(path,".");
	else
		sprintf(path,"%s",argv[1]);
	return prtf(path);
}
