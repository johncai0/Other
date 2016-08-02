#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/vfs.h>

#define MAXLINE	2048
#define MAXCPU	255
#define MAXDSK	255

typedef struct cpuvar {
	char cpuname[MAXLINE];
	long unsigned int user;
	long unsigned int nice;
	long unsigned int system;
	long unsigned int idle;
	long unsigned int iowait;
	long unsigned int irq;
	long unsigned int softirq;
	long unsigned int stealstolen;
	long unsigned int guest;
	long unsigned int oth;
} cpu;

typedef struct diskvar {
        char path[MAXLINE];
	char dev[MAXLINE];
        long bts;
        long bfs;
        long its;
        long ifs;
} disk;

int equs(char *d,char *s);
