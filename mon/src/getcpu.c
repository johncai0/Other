#include "mon.h"
int getcpu(void)
{
	char *file="/proc/stat";
	FILE *fp = NULL;
	char line[MAXLINE]="";
	char cpuname[8]="";
	struct cpuvar cpu[MAXCPU];
	int i=0;
	if ((fp = fopen(file,"r")) == NULL)
	{
		fprintf(stderr,"[getcpu]->[open]:: ERRNO: [%s]  CASE: %s\n",file,strerror(errno));
		return -1;
	}
	for (i=0;fgets(line,MAXLINE, fp) != NULL && equs("cpu",line) && i<MAXCPU; i++) {
		//fprintf(stdout,"%s\n",line);
		sscanf(line,"%s %d %d %d %d %d %d %d %d %d %d",cpuname,&(cpu[i].user),&(cpu[i].nice),&(cpu[i].system),&(cpu[i].idle),
			&(cpu[i].iowait),&(cpu[i].irq),&(cpu[i].softirq),&(cpu[i].stealstolen),&(cpu[i].guest),&(cpu[i].oth));
		strcpy(cpu[i].cpuname,cpuname);
		fprintf(stdout,"%s %d %d %d %d %d %d %d %d %d %d\n",cpu[i].cpuname,cpu[i].user,cpu[i].nice,cpu[i].system,
				cpu[i].idle,cpu[i].iowait,cpu[i].irq,cpu[i].softirq,cpu[i].stealstolen,cpu[i].guest,cpu[i].oth);
	}
	fprintf(stdout,"Total CPU Number: %d\n",i-1);
	return 0;
}
int main(void)
{
	return getcpu();
}
