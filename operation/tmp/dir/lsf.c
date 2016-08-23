#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int strstart(const char *src,const char *des) {
	if (strstr(src,des) == src && strlen(src) == strlen(des))
		return 0;
	return 1;
}
int isdir(char *path)
{
 struct stat st;
 stat(path,&st);
 if (S_ISDIR(st.st_mode))
  	return 1;
 else
 	return 0;
}

void prtf(char *path) {
	DIR *dir;
	struct dirent *ptr;
	char buf[4096]={0};
	dir = opendir(path);
	while ((ptr  = readdir(dir)) != NULL && fprintf(stderr,"prtf.readdir[ERROR]: %s!\n",strerror(errno))) {
		if (strstart(ptr->d_name,".")&strstart(ptr->d_name,"..")) {
			if (isdir(ptr->d_name)) {
				sprintf(buf,"%s/%s",path,ptr->d_name);
				printf("%s\n",buf);
				prtf(buf);
			}
			else {
				sprintf(buf,"%s/%s",path,ptr->d_name);
				printf("%s\n",buf);
			}
		}
	}
	closedir(dir);
}

int main(int argc,char **argv) {
	char *path=".";
	if (argv[1])
		prtf(argv[1]);
	else
		prtf(path);
	return 0;
}
