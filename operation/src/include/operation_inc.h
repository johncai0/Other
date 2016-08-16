//bind ip:port to this server
//ok socket returned, error return -1
int ser_bind(char *ip, int port);

//print help mesages
//void
void help();

//create epoll fd and add serfd to epollfd
//ok epoll fd returned, error return -1
int epoll_fd_create(int serfd);

//epoll event pool size
#define EPS 1024
