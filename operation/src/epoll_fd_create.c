#include "include/os_inc.h"
#include <sys/epoll.h>
int epoll_fd_create(int serfd) {
	int epfd = -1;
        if ((epfd = epoll_create(EPS)) == -1)
        {
                fprintf(stderr,"epoll_fd_create.epoll_create[ERROR]: %s!\n",strerror(errno));
                return -1;
        }
        struct epoll_event event_ctl;
        event_ctl.data.fd = serfd;
        event_ctl.events = EPOLLIN | EPOLLET;
        struct epoll_event event_pool[EPS];
        if (epoll_ctl(epfd,EPOLL_CTL_ADD,serfd,&event_ctl) == -1) {
                fprintf(stderr,"epoll_fd_create.epoll_ctl[ERROR]: %s!\n",strerror(errno));
                return -1;
        }
	return epfd;
}
