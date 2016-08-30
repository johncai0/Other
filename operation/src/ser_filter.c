#include "include/os_inc.h"
#include "include/operation_inc.h"
int ser_strbgen_eq(char *src, char *des) {
	if (strstr(src,des) != src)
		return -1;
	else
		return 0;
}
int ser_cmdfilter(char *conf,int *sockfd) {
	char buffer[BUFFSIZE]={0};
	int stat=-1;
	if (!ser_strbgen_eq(conf,HOME)) {
		//fprintf(stdout,"recv set host to %s!\n",conf);
		if ((stat = chtodir(conf)) != 0) {
			sprintf(buffer,"ERROR: change to dir [%d] %s",stat,strerror(stat));
			fprintf(stderr,"%s\n",buffer);
		} else {
			sprintf(buffer,"ok");
			fprintf(stdout,"Change Current Dir Ok.\n");
		}
		if (write(*sockfd, buffer, strlen(buffer)) == strlen(buffer)) {
			fprintf(stdout,"Send To Client Status Ok\n");
		} else {
			fprintf(stderr,"send to client Error [socket %s]!\n",strerror(errno));
			//epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
			//close_conn(sockfd);
		}
		return 0;
	} else if (!ser_strbgen_eq(conf,RCMD)) {
		fprintf(stdout,"run commond!\n");
		return 0;
	} else if (!ser_strbgen_eq(conf,ADDF)) {
		fprintf(stdout,"server add file\n");
		return 0;
	} else if (!ser_strbgen_eq(conf,ADDD)) {
		if ((stat = mymkdir(conf)) != 0) {
			sprintf(buffer,"ERROR:mkdir dir [%d] %s",stat,strerror(stat));
			fprintf(stderr,"%s\n",buffer);
		} else {
			sprintf(buffer,"ok");
			fprintf(stdout,"mkdir Dir Ok.\n");
		}
		if (write(*sockfd, buffer, strlen(buffer)) == strlen(buffer)) {
			fprintf(stdout,"Send To Client Status Ok\n");
		} else {
			fprintf(stderr,"send to client Error [socket %s]!\n",strerror(errno));
		}
		return 0;
	} else if (!ser_strbgen_eq(conf,COVF)) {
		fprintf(stdout,"server cover file\n");
		return 0;
	} else if (!ser_strbgen_eq(conf,COVD)) {
		fprintf(stdout,"server cover dir\n");
		return 0;
	} else if (!ser_strbgen_eq(conf,DELF)) {
		fprintf(stdout,"server delete file\n");
		return 0;
	} else if (!ser_strbgen_eq(conf,DELD)) {
		fprintf(stdout,"server delete dir\n");
		return 0;
	} else {
		fprintf(stdout,"recv file [%s]\n",conf);
		fprintf(stdout,"config file ERROR!\n");
		return -1;
	}
}
