#include "server.h"
/*create a socket file and set address reuse
 *args: null
 *return: a socket fd
 * */
int sock_add(void)
{
	int fd;
	int option = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr,"[sock_add] socket ERROR:: %s\n",strerror(errno));
	}
	if (setsockopt (fd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option)) < 0)
	{
		fprintf(stderr,"[sock_add] setsockopt ERROR:: %s\n",strerror(errno));
	}
	return fd;
}
/*
 *address bind to socket
 *args: socket fd,ip address and port number
 *not return parameter
 * */
void sock_bind(int fd, int port, char *ip)
{
	struct sockaddr_in sin;
	int sin_size;
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(port);
	if (ip == NULL)
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
	else
		sin.sin_addr.s_addr = inet_addr(ip);
	if (bind(fd, (struct sockaddr *)(&sin), sizeof (struct sockaddr)) == -1)
	{
		fprintf(stderr,"[sock_bind] bind ERROR:: %s\n",strerror(errno));
		exit(1);
	}
}

/*
 * master body
 * loop client
 * args: server listen socket 
 * return void
 * */
void loop(int serfd) 
{
	int cli_fd;
	struct sockaddr_in cli_addr;
	char buf[8192];
	socklen_t sin_size = sizeof(cli_addr);
	while (1) {
		if ((cli_fd = accept(serfd,(struct sockaddr*)&cli_addr,&sin_size)) == -1)
		{
			fprintf(stderr,"[loop] accept ERROR:: %s\n",strerror(errno));
		} else {
			printf("new client :: %s:%d\n",inet_ntoa(cli_addr.sin_addr),htons(cli_addr.sin_port));
			memset(buf,'\0',sizeof buf);
			read(cli_fd,buf,sizeof buf);
			printf("%s\n\n", buf);
			write(cli_fd,"HTTP 200\n",sizeof("HTTP 200\n"));
		}
	}
}

int main(int argc, char **argv)
{
	int ser_fd;
	if ((ser_fd = sock_add()) == -1) {
		fprintf(stderr,"error add socket return -1\n");
		return ser_fd;
	}
	sock_bind(ser_fd,8080,NULL);
	if (listen(ser_fd,MAX_QUE) == -1) {
		fprintf(stderr,"[MAIN] listen ERROR:: %s\n",strerror(errno));
		return -1;
	}
	loop(ser_fd);
	sleep(1000);
	fprintf(stdout,"hello word!\n");
	return 0;
}
