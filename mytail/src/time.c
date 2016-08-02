#include <stdio.h>
#include <time.h>
#include <string.h>

void gettm(char *stm)
{
	time_t mytm;
	struct tm *tminfo;
	time(&mytm);
	tminfo = localtime(&mytm);
	tminfo->tm_year += 1900;
	tminfo->tm_mon++;
	sprintf(stm,"\t\"time\":\"%d-%02d-%02d %02d:%02d:%02d\",\n\t\"sec\":\"%d\",\n",
		tminfo->tm_year,tminfo->tm_mon,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min,tminfo->tm_sec,mytm);
}
int main(void)
{
	char len[54];
	gettm(len);
	printf("%s",len);
	return 0;
}
