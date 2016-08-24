//epoll event pool size
#define EPS		102400
#define BUFFSIZE	1024
#define LISTENBACKLOG	100
#define PATHSIZE	4096

//bind ip:port to this server
//ok socket returned, error return -1
int ser_bind(char *ip, int port);

//print help mesages
//void
void help();

//create epoll fd and add serfd to epollfd
//ok epoll fd returned, error return -1
int epoll_fd_create(int serfd);

//loop comming connection
//void
void body_loop(int epfd,int listenfd,struct epoll_event event_pool[EPS]); 

//string is eq
int strstart(const char *src,const char *des);

//scandir
int scdirect(char *path);

//scanfile
int prtf(char *path); 

//connect to server
//error return -1, ok return socketfd
int connect_ser(char *ip, int port);

//filter config comm
//ok return 0, error return -1
int cmdfilter(char *conf, int socketfd);
