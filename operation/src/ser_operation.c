#include "include/os_inc.h"
#include "include/operation_inc.h"

int chtodir(char *conf) {
	char dest[PATHSIZE]={0};
	sscanf(conf,"%*s %s",dest);
	int stat=-1;
	if ((stat = chdir(dest)) == -1) {
		fprintf(stderr,"chdir to [%s] %s\n", dest, strerror(errno));
		return errno;
	}
	return 0;
}
int mymkdir(char *conf) {
	char dest[PATHSIZE]={0};
	sscanf(conf,"%*s %s",dest);
	if (mkdir(dest,DFMD) == -1) {
		fprintf(stderr,"mymkdir [%s] %s\n", dest,strerror(errno));
		return errno;
	}
	return 0;
}
