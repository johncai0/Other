#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <pthread.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
struct dskstat {
        char name[16];
        char mntp[64];
        double inodeuse;
        double usespace;
};
int strsmstr(char *a, char *b);
int main(int argc,char **argv)
{

	char buffer[1024], *HELOST="helo";
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(1032);
	bind(listenfd,(struct sockaddr *)&addr,sizeof(addr));
	listen(listenfd, 100);
	ssize_t t;
	double cpu_stat,mem_stat;
	struct dskstat dsk_stat[31];
	int y=0;

	for(;;)
	{
		int connfd=accept(listenfd, NULL, NULL);

		memset(buffer, 0, 1024);		
		//t=read(connfd, buffer, 1024);
		read(connfd, buffer, sizeof(buffer));
		if (strsmstr(buffer,HELOST) != 0 ) {
			fprintf(stderr,"Requst ERROR!\n");
			close(connfd);
			return -7;
		}
		else {
		write(connfd, "GETCPU", sizeof("GETCPU"));
		t=read(connfd, &cpu_stat, sizeof(cpu_stat));
		fprintf(stdout, "CPU STAT(%): %0.2f\n", cpu_stat);
		write(connfd, "GETMEM", sizeof("GETMEM"));
		t=read(connfd, &mem_stat, sizeof(mem_stat));
		fprintf(stdout, "MEM STAT(%): %0.2f\n", mem_stat);
		write(connfd, "GETDSK", sizeof("GETDSK"));
                t=read(connfd, &dsk_stat, sizeof(dsk_stat));
		while (dsk_stat[y].inodeuse) {
                fprintf(stdout, "%s: %s use: (%0.2f%)\tinode_use: (%2.0f%)\n", 
			dsk_stat[y].mntp, dsk_stat[y].name, dsk_stat[y].usespace, dsk_stat[y].inodeuse);
			y++;
		}
		y = 0;
		write(connfd, "EXIT", 100);
		close(connfd);
		}	
	}

	return 0;
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
