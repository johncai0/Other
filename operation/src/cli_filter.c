#include "include/os_inc.h"
#include "include/operation_inc.h"
#define HOST	"host:"
#define HOME	"home:"
#define RCMD	"rcmd:"
#define ADDF	"addf:"
#define ADDD	"addd:"
#define COVF	"covf:"
#define COVD	"covd:"
#define DELF	"delf:"
#define DELD	"deld:"
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
int cmdfilter(char *conf,int sockfd) {
	if (!strbgen_eq(conf,HOST)) {
		fprintf(stdout,"connect to server!\n");
		if ((sockfd=myconnect(conf)) == -1) {
			fprintf(stderr,"config cmd %s run error.\n",conf);
			return -1;
		}
		return 0;
	} else if (!strbgen_eq(conf,HOME)) {
		fprintf(stdout,"get home path\n");
		return 0;
	} else if (!strbgen_eq(conf,RCMD)) {
		fprintf(stdout,"run commond!\n");
		return 0;
	} else if (!strbgen_eq(conf,ADDF)) {
		fprintf(stdout,"server add file\n");
		return 0;
	} else if (!strbgen_eq(conf,ADDD)) {
		fprintf(stdout,"server add directory\n");
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
