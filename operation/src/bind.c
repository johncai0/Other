#include "include/os_inc.h"
#include "include/operation_inc.h"
int ser_bind(char *ip, int port){
	int sock=-1;
	if (port <= 0 || port >= 65535) {
		fprintf(stderr,"Error Port Number Is Bad: %d\n",port);
		help();
		exit(-1);
	}
	if ((sock=socket(AF_INET,SOCK_STREAM,0))==-1) {
		fprintf(stderr,"ser_bind.socket[ERROR]: %s!\n",strerror(errno));
		exit(-1);
	}
	int flag=1;
        if (setsockopt(sock,SOL_SOCKET, SO_REUSEADDR,&flag,sizeof(int)) == -1) {
                fprintf(stderr,"ser_bind.setsockop[ERROR]: %s!\n",strerror(errno));
                exit(-1);
        }
	struct sockaddr_in addr;
	bzero(&addr,sizeof(bzero));
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if (bind(sock,(struct sockaddr *)&addr,sizeof(addr)) == -1){
		fprintf(stderr,"ser_bind.bind[ERROR]: %s!\n",strerror(errno));
		exit(-1);
	}
	if (listen(sock,100) == -1) {
		close(sock);
		fprintf(stderr,"ser_bind.listen[ERROR]: %s!\n", strerror(errno));
		exit(-1);
	}
	fprintf(stdout,"Server Listen to:%s:%d\n",ip,port);
	return sock;
}
