#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <pthread.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv)
{

	char buffer[1024];
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(1032);
	bind(listenfd,(struct sockaddr *)&addr,sizeof(addr));
	listen(listenfd, 100);
	ssize_t t;

	for(;;)
	{
		int connfd=accept(listenfd, NULL, NULL);

		memset(buffer, 0, 1024);		
		t=read(connfd, buffer, 1024);
		fprintf(stdout, "Mem STAT: %s\n", buffer);
		write(connfd, "Mem Status SerRec Ok!", 100);
		close(connfd);	
	}

	return 0;
}

