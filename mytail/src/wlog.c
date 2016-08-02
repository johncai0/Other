#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
int logr(char *buf) {
	FILE *fp;
	size_t i;
	char log[8192];
	if ((fp = fopen("./log/mytail.log","a+")) == NULL) {
		fprintf(stderr,"open log file: %s\n",strerror(errno));
		return -1;
	}
	time_t mytm;
	struct tm *tminfo;
	time(&mytm);
	tminfo = localtime(&mytm);
	tminfo->tm_year += 1900;
	tminfo->tm_mon++;
	sprintf(log,"[%d-%d-%d %d:%d:%d] %s",
		tminfo->tm_year,tminfo->tm_mon,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min,tminfo->tm_sec,buf);
	if ((i = fwrite(log,strlen(log),1,fp)) != 1) {
		fprintf(stderr,"write log file: %s\n",strerror(errno));
		return -1;
	}
	return 0;
}
int main(void)
{
	char *a = "test log file!\n";
	if (logr(a) != 0)
		printf("error!\n");
	return 0;
}
