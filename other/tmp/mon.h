#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MAXLINE	2048
#define MAXCPU	255

typedef struct cpuvar {
	char cpuname[8];
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
