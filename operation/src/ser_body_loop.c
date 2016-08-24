#include "include/os_inc.h"
#include "include/operation_inc.h"

void my_recv(int epfd, int sockfd, int listenfd)
{
	char *html="HTTP/1.1 200 OK\r\n\r\n<h1>Hello Word!!!</h1>";
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
		char buffer[BUFFSIZE];
		bzero(buffer,BUFFSIZE);
		int size = read(sockfd, buffer, BUFFSIZE);
		//write(1, buffer, size);
		printf("%s\n",buffer);
		write(sockfd, html, strlen(html));
		epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
		close(sockfd);
	}
}

void body_loop(int epfd,int listenfd,struct epoll_event event_pool[EPS]) {
	int n,sockfd,nfd=-1;
	if ((nfd = epoll_wait(epfd,event_pool,EPS,-1)) == 0) {
                        fprintf(stdout,"body_loop.epoll_wait[timeout]: %s!\n",strerror(errno));
                } else if ( nfd == -1) {
                        fprintf(stderr,"body_loop.epoll_wait[ERROR]: %s!\n",strerror(errno));
                } else {
                        for (n = 0; n < nfd; n++) {
                                sockfd = event_pool[n].data.fd;
                                if (event_pool[n].events & EPOLLIN) {
                                        my_recv(epfd,sockfd,listenfd);
                                }
                        }
                }
}
