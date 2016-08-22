#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

main()
{
	int listenfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr,caddr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(80);
	char buff[2048];
	bind(listenfd,(struct sockaddr *)&addr,sizeof(addr));
	listen(listenfd, 102400);
	char strings[]="HTTP/1.1 200 OK\r\nServer: MyServer1.2\r\nSD: This's A Test Web Server!!!\r\n\r\n<html><head><title>TEST</title></head><body><h3>Hello word!!!</h3></body></html>";
	char buffer[1024];
	//---------------------------
	//struct sockaddr *peersa;
	 unsigned int len=sizeof(caddr);
	//---------------------------
	for (;;) {
		int connfd=accept(listenfd, NULL, NULL);
		//int connfd=accept(listenfd, (struct sockaddr *) &caddr, &len);
		//int connfd=accept(listenfd, (struct sockaddr)caddr, &peerlen);
	//	fprintf(stdout,"IP: %s\nPort: %d\n", inet_ntop(AF_INET, &caddr.sin_addr, buff,sizeof(buff)),ntohs(caddr.sin_port));
		bzero(buffer,sizeof(buffer));
		read(connfd, buffer, sizeof(buffer));
		fprintf(stdout,"Client's Return: \"%s\"\n",buffer);
		write(connfd, strings,strlen(strings));
		//read(connfd,buffer,sizeof(buffer));
		//fprintf(stdout,"%s",buffer);
		close(connfd);
	}
}
