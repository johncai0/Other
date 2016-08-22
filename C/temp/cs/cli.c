#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <pthread.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statfs.h>
int strsmstr(char *a, char *b);
double get_cpu();
double get_mem();
struct cpustat {
        char name[20];
        unsigned int user;
        unsigned int nice;
        unsigned int system;
        unsigned int idle;
	unsigned int iowait;
	unsigned int irq;
	unsigned int softirq;
};
struct dskstat {
        char name[16];
        char mntp[64];
        double inodeuse;
        double usespace;
};
int get_dsk(struct dskstat *dskst);

int main(int argc,char **argv)
{

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	addr.sin_port=htons(1032);
	char buffer[1024], *HELOST = "helo", *REQOPCPU="GETCPU",*REQOPEXT="EXIT",*REQOPMEM="GETMEM",*REQOPDSK="GETDSK";
	double cpu_stat,mem_stat;
	struct dskstat dsk_stat[31];
	int i;

	if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0) {
		fprintf(stderr, "connect fat!\n");
		return -4;
	}
	if (write(sockfd, HELOST, sizeof(HELOST)) != sizeof(HELOST)) {
		fprintf(stderr, "Send HELOST ERROR!\n");
	}
	read(sockfd, buffer, 1024);
	while (strsmstr(buffer,REQOPEXT) != 0) {
		if (strsmstr(buffer,REQOPCPU) == 0 ) {
			printf("Send: \"Send CPU status!\"\n");
			if ((cpu_stat = get_cpu()) < 0) {
				fprintf(stderr, "getcpu use ERROR!\n");
				return -3;
			}
	        	if (write(sockfd, &cpu_stat, sizeof(cpu_stat)) != sizeof(cpu_stat)) {
       	        		fprintf(stderr, "Send cpu_stat ERROR!\n");
			}
			fprintf(stdout, "%s\n", buffer);	
			memset(buffer, 0, 1024);
			read(sockfd, buffer, 1024);
		}
                else if (strsmstr(buffer,REQOPMEM) == 0 ) {
                        printf("Send: \"Send MEM status!\"\n");
                        if ((mem_stat = get_mem()) < 0) {
                                fprintf(stderr, "getmem use ERROR!\n");
                                return -3;
                        }
                        if (write(sockfd, &mem_stat, sizeof(mem_stat)) != sizeof(mem_stat)) {
                                fprintf(stderr, "Send mem_stat ERROR!\n");
                        }
                        fprintf(stdout, "%s\n", buffer);
                        memset(buffer, 0, 1024);
                        read(sockfd, buffer, 1024);
                }
		else if (strsmstr(buffer,REQOPDSK) == 0 ) {
                        printf("Send: \"Send DSK status!\"\n");
                        if ((i = get_dsk(dsk_stat)) < 0) {
                                fprintf(stderr, "getdsk use ERROR!\n");
                                return -3;
                        }
                        if (write(sockfd, &dsk_stat, sizeof(dsk_stat)) != sizeof(dsk_stat)) {
                                fprintf(stderr, "Send mem_stat ERROR!\n");
                        }
                        fprintf(stdout, "%s\n", buffer);
			fprintf(stdout, "%s: %s use: (%0.2f%)\tinode_use: (%2.0f%)\n", 
			dsk_stat[1].mntp, dsk_stat[1].name, dsk_stat[1].usespace, dsk_stat[1].inodeuse);
			printf("%d\n", i);
                        memset(buffer, 0, sizeof(buffer));
                        read(sockfd, buffer, 1024);
                }
		else {		
			printf("Req ERROR: %s\n", buffer);
			memset(buffer, 0, 1024);
			close(sockfd);
			return -9;
		}
	}
	fprintf(stderr,"Receive EXIT to quit!\n");
	close(sockfd);
	return 0;
}
double get_cpu()
{
	struct cpustat oldcpustat;
	struct cpustat newcpustat;
	int cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
	unsigned int total_use,total,total1,total_use1;
	FILE *f;
	double avg,cpu;
	char buf[256],buf1[256];
	if ((f = fopen("/proc/stat","r")) == NULL)
	{
		fprintf(stderr,"ERROR: Open File /proc/stat Failure!\n");
		return -1;
	}
	fgets(buf, sizeof(buf), f);
	fclose(f);
	sscanf(buf,"%s%u%u%u%u%u%u%u", oldcpustat.name, &(oldcpustat.user), &(oldcpustat.nice), 
		&(oldcpustat.system), &(oldcpustat.idle),&(oldcpustat.iowait),&(oldcpustat.irq),&(oldcpustat.softirq));
	//fprintf(stdout, "%s %u %u %u %u %u %u %u\n", oldcpustat.name, oldcpustat.user, oldcpustat.nice,
		//oldcpustat.system, oldcpustat.idle,oldcpustat.iowait,oldcpustat.irq,oldcpustat.softirq);
	total= oldcpustat.user + oldcpustat.nice + oldcpustat.system + oldcpustat.idle 
		+ oldcpustat.iowait + oldcpustat.irq + oldcpustat.softirq;
	sleep(1);
	if ((f = fopen("/proc/stat","r")) == NULL)
        {
                fprintf(stderr,"ERROR: Open File /proc/stat Failure!\n");
                return -2;
        }
        fgets(buf1, sizeof(buf), f);
	fclose(f);
        sscanf(buf1,"%s%u%u%u%u%u%u%u", newcpustat.name, &(newcpustat.user), &(newcpustat.nice),
                &(newcpustat.system), &(newcpustat.idle),&(newcpustat.iowait),&(newcpustat.irq),&(newcpustat.softirq));
	total1= newcpustat.user + newcpustat.nice + newcpustat.system + newcpustat.idle
                + newcpustat.iowait + newcpustat.irq + newcpustat.softirq;
	avg =  ((double)total_use1 - (double)total_use) / ((double)total1 - (double)total) * 100;
	int total_idle = oldcpustat.user + oldcpustat.nice + oldcpustat.system +
                        oldcpustat.iowait + oldcpustat.irq + oldcpustat.softirq;
	int total_idle1 = newcpustat.user + newcpustat.nice + newcpustat.system +
                        newcpustat.iowait + newcpustat.irq + newcpustat.softirq;
	cpu =   ((double)total_idle1 - (double)total_idle) / ((double)total1 - (double)total) * 100;	
	//fprintf(stdout, "   avg_use: %0.2f\%\n", cpu);
	return cpu;
}
int strsmstr(char *a, char *b)
{
        for (; *a && *b; a++, b++) {
                if (*a != *b) {
                        return -5;
                        fprintf(stderr,"The Requst ERROR!\n");
                }
        }
        if (*a || *b) {
                return -6;
                fprintf(stderr,"The Requst too long/short!\n");
        }
        return 0;
}
int get_dsk(struct dskstat sdkst[31])
{
	FILE *fp;
	char buf[512],*tmstr = "/dev/",*str1p,*str2p,*temp;
	int i,y=0;
	//struct dskstat sdkst[31];
	struct statfs stat;
	if((fp=fopen("/etc/mtab","r")) == NULL) {
		fprintf(stderr,"ERROR: Open mtab ERROR!\n");
		return -9;
	}
	while (fgets(buf, sizeof(buf),fp) != NULL) {
		for (str1p = tmstr,str2p = buf,i = 0; *str1p == *str2p; str1p++,str2p++,i++)
			;
		if (i == 5) {
			sscanf(buf,"%s %s %s",&(sdkst[y].name),&(sdkst[y].mntp), &temp);
			statfs(sdkst[y].mntp, &stat);
			sdkst[y].inodeuse = 100 - ((double)stat.f_ffree / (double)stat.f_files * 100);
			sdkst[y].usespace = 100 - ((double)stat.f_bfree / (double)stat.f_blocks * 100);
			y++;
		}
	}
	return y;
}
double get_mem()
{
        FILE *fp;
        char buf[512];
        int i;
        long long int total, free, cache;
        double t;
        if ((fp=fopen("/proc/meminfo","r")) == NULL)
        {
                fprintf(stderr,"ERROR: Open meminfo ERROR!");
                return -8;
        }
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"MemTotal: %lld kB", &total);
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"MemFree: %lld kB", &free);
        fgets(buf,sizeof(buf),fp);
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"Cached: %lld kB", &cache);
        t = (double)((long double)(total - (cache + free)) / (long double)(total) * 100);
        return t;
}
