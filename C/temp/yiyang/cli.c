
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("188.188.3.240");
	//addr.sin_addr.s_addr=inet_addr("188.188.3.240");
	addr.sin_port=htons(1111);
	//addr.sin_port=htons(80);
	if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0) {
		fprintf(stderr, "connect fat!\n");
		return -4;
	}


	char helo[] ="GET / HTTP/1.1\r\nHost: www.unix6.com:80\r\nUser-Agent: MyClient_WEB\r\n\r\n";
	write(sockfd, helo, strlen(helo));

	char buffer[4096] = {0};
	size_t size = read(sockfd, buffer, sizeof(buffer));
	write(1, buffer, sizeof(buffer));

	close(sockfd);

	return 0;
}
