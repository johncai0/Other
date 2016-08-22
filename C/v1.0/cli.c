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

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	addr.sin_port=htons(1032);
	char buffer[1024];

	connect(sockfd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	printf("Send: \"Send Mem status!\"\n");
	write(sockfd, "Mem status!", 100);
	read(sockfd, buffer, 1024);
	fprintf(stdout, "%s\n", buffer);	
	memset(buffer, 0, 1024);
	close(sockfd);
	return 0;
}

