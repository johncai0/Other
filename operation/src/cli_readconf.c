#include "include/os_inc.h"
#include "include/operation_inc.h"
FILE *openfile(char *path) {
        FILE *fp = NULL;
        if ((fp=fopen(path,"r")) == NULL) {
                fprintf(stderr,"openfile.fopen[ERROR]: %s %s!\n",path,strerror(errno));
        }
	return fp;
}
int getlen(FILE *fp, char *buf) {
	if (fgets(buf,PATHSIZE*2+100, fp) == NULL) 
		return 0;
	buf[strlen(buf)-1]='\0';
	return strlen(buf);
}
int readconf(char *path) {
	FILE *conf;
	int sockfd=-1;
	int num=0;
	char buffer[PATHSIZE*2+100]={0};
	if ((conf=openfile(path))==NULL)
		return -1;
	while (getlen(conf,buffer) != 0) {
		num++;
		fprintf(stdout,"%s\n",buffer);
		if (cmdfilter(buffer,&sockfd) != 0) {
			fprintf(stderr,"config commond error in %d line!\n",num);
			return -1;
		}
		//fprintf(stdout,"sockfd == %d\n", sockfd);
	}
	return 0;
}
