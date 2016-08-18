#include "include/os_inc.h"
#include "include/operation_inc.h"

int main(int argc, char **argv)
{
	int serfd=-1;
	if (argc < 3) {
		help();
		return -1;
	}
	if ((serfd=ser_bind(argv[1],atoi(argv[2]))) == -1) {
		fprintf(stderr,"ser_bind ERROR!\n");
		return -1;
	}
	int epfd = -1;
	if ((epfd=epoll_fd_create(serfd)) == -1) {
		fprintf(stderr,"epoll_fd_create ERROR!\n");
		return -1;
	}
	struct epoll_event event_pool[EPS];
	while(1) {
		body_loop(epfd,serfd,event_pool);
	}
	return 0;
}
