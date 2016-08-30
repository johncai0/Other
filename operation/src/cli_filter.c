#include "include/os_inc.h"
#include "include/operation_inc.h"
int strbgen_eq(char *src, char *des) {
	if (strstr(src,des) != src)
		return -1;
	else
		return 0;
}
int myconnect(char *conf) {
	char host[64]={0};
	char sport[6]={0};
	int port=0;
	int sockfd=-1;
	if (sscanf(conf,"%*s%s%s",host,sport) != 2) {
		fprintf(stderr,"host or port error in conf[%s]\n",conf);
		return -1;
	}
	port = atoi(sport);
	if ((sockfd=connect_ser(host,port)) == -1) {
		fprintf(stderr,"connect to server %s:%d error!\n",host,port);
		return -1;
	}
	return sockfd;
}
void close_conn(int fd)
{
        fprintf(stdout,"close connection %d \n",fd);
        shutdown(fd,SHUT_RDWR);
        close(fd);
}
int cmdfilter(char *conf,int *sockfd) {
	char buffer[BUFFSIZE]={0};
	if (!strbgen_eq(conf,HOST)) {
		if ((*sockfd=myconnect(conf)) == -1) {
			fprintf(stderr,"config cmd %s run error.\n",conf);
			return -1;
		}
		fprintf(stdout,"connect to server sockfd = %d!\n",*sockfd);
		return 0;
	} else if (!strbgen_eq(conf,HOME)) {
		fprintf(stdout,"sockfd = %d\n",*sockfd);
		write(*sockfd, conf, strlen(conf));
		read(*sockfd, buffer, BUFFSIZE);
		fprintf(stdout,"send home path,recv status %s\n",buffer);
		return 0;
	} else if (!strbgen_eq(conf,RCMD)) {
		fprintf(stdout,"run commond!\n");
		return 0;
	} else if (!strbgen_eq(conf,ADDF)) {
		fprintf(stdout,"server add file\n");
		return 0;
	} else if (!strbgen_eq(conf,ADDD)) {
		fprintf(stdout,"sockfd = %d\n",*sockfd);
		write(*sockfd, conf, strlen(conf));
		read(*sockfd, buffer, BUFFSIZE);
		fprintf(stdout,"server add directory %s\n",buffer);
		return 0;
	} else if (!strbgen_eq(conf,COVF)) {
		fprintf(stdout,"server cover file\n");
		return 0;
	} else if (!strbgen_eq(conf,COVD)) {
		fprintf(stdout,"server cover dir\n");
		return 0;
	} else if (!strbgen_eq(conf,DELF)) {
		fprintf(stdout,"server delete file\n");
		return 0;
	} else if (!strbgen_eq(conf,DELD)) {
		fprintf(stdout,"server delete dir\n");
		return 0;
	} else {
		fprintf(stdout,"config file ERROR!\n");
		return -1;
	}
}
