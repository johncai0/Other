#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>


int cai_bind(char *ip, int port)
{
	int sock = -1;
	if ((sock = socket(AF_INET,SOCK_STREAM,0)) == -1) {
		fprintf(stderr,"socket fun ERROR!\n");
		exit(-1);
	}
	int flag=1;
	if (setsockopt(sock,SOL_SOCKET, SO_REUSEADDR,&flag,sizeof(int)) == -1) {
		fprintf(stderr,"setsockop fun ERROR!\n");
		exit(-1);
	}
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if (bind(sock,(struct sockaddr *)&addr,sizeof(addr)) == -1) {
		close(sock);
		fprintf(stderr,"bind fun ERROR!\n");
		exit(-1);
	}
	if (listen(sock,100) == -1) {
		close(sock);
		fprintf(stderr,"listen fun ERROR!\n");
		exit(-1);
	}
	return sock;
}

void my_recv(int epfd, int sockfd, int listenfd)
{
	struct sockaddr_in cliaddr;
	int sockaddr_len = sizeof(struct sockaddr_in);
	bzero(&cliaddr,sockaddr_len);
	if (sockfd == listenfd) {
		int clientfd = accept4(listenfd, &cliaddr, &sockaddr_len, SOCK_NONBLOCK | SOCK_CLOEXEC);
		printf("new client :: %s:%d\n",inet_ntoa(cliaddr.sin_addr),htons(cliaddr.sin_port));
		if (clientfd > 0) {
			struct epoll_event event_ctl;
			event_ctl.data.fd = clientfd;
			event_ctl.events = EPOLLIN | EPOLLET;
			epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &event_ctl);
		}
	} else {
		char buffer[1024];
		int size = read(sockfd, buffer, 1024);
		write(1, buffer, size);
		write(sockfd, "ok", 2);
		close(sockfd);
	}
}

int main(void)
{
	int serfd = -1;
	if ((serfd = cai_bind("127.0.0.1",80)) == -1) {
		fprintf(stderr,"cai_bind fun ERROR!\n");
		exit(-1);
	}
	int epfd = -1;
	if ((epfd = epoll_create(1024)) == -1)
	{
		fprintf(stderr,"epoll_create fun ERROR!\n");
		exit(-1);
	}
	struct epoll_event event_ctl;
	event_ctl.data.fd = serfd;
	event_ctl.events = EPOLLIN | EPOLLET;
	struct epoll_event event_pool[1024];
	if (epoll_ctl(epfd,EPOLL_CTL_ADD,serfd,&event_ctl) == -1) {
		fprintf(stderr,"epoll_ctl fun ERROR@\n");
		exit(-1);
	}
	int n, sockfd, nfd = -1;
	while (1) {
		if ((nfd = epoll_wait(epfd,event_pool,1024,-1)) == 0) {
			fprintf(stdout,"epoll_wait fun timeout!\n");
		} else if ( nfd == -1) {
			fprintf(stderr,"epoll_wait fun ERROR!\n");
		} else {
			for (n = 0; n < nfd; n++) {
				sockfd = event_pool[n].data.fd;
				if (event_pool[n].events & EPOLLIN) {
					my_recv(epfd,sockfd,serfd);	
				}
			}
		}
	}
}
