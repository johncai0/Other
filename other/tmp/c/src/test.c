#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int writelog(char *str,char *filepath) {
	int fd;
	FILE *file;
	if ((fd = open(filepath,O_RDWR|O_CREAT|O_NOCTTY|O_APPEND,777)) == -1) {
		fprintf(stderr,"ERROR:[open] %s\n",strerror(errno));
		return -6;
	}
	if ((file = fdopen(fd,"a+")) == NULL) {
		fprintf(stderr,"ERROR:[fopen] %s\n",strerror(errno));
		return -7;
	}
	if ( (fwrite(str, strlen(str), 1, file)) != 1) {
		fprintf(stderr,"ERROR:[fwrite] write error (%s)\n",strerror(errno));
		return -8;
	}
	fclose(file);
	close(fd);
	return 0;
}

char *printhtml()
{
	return "HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nContent-Type: text/html; charset=utf-8\r\nServer: MyTools\r\n\r\n\r\n<html><head><title>reload</title></head><body bgcolor=\"white\"><center><h1>Nginx is reload</h1></center><hr><center>MyTools</center></body></html>";
}
char *printerrhtml()
{
	return "HTTP/1.1 404 Not Found\r\nConnection: keep-alive\r\nContent-Type: text/html; charset=utf-8\r\nServer: MyTools\r\n\r\n\r\n<html><head><title>reload</title></head><body bgcolor=\"white\"><center><h1>Nginx reload ERROR</h1></center><hr><center>MyTools</center></body></html>";
}

char strtime[64];
char *getnow()
{
	time_t nowtime;
	struct tm *timeinfo;
	time( &nowtime );
	timeinfo = localtime( &nowtime );
	int year, month, day;
	year = timeinfo->tm_year + 1900;
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;
	memset(&strtime,0,sizeof(strtime));
	sprintf(strtime,"%d-%d-%d %d:%d:%d", year, month, day,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	return strtime;
}
int main(int argc, char **argv) 
{
	if (fork() != 0) {
		exit(0);
	}
	int server_sockfd, client_sockfd;
	struct sockaddr_in server_addr,client_addr;
	memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr,0,sizeof(client_addr));
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(8000);
	char buff[8192];
	char buff1[8192];
	memset(&buff,0,8192);
	memset(&buff1,0,8192);
	int status=0;
	char stdlog[512];
	char errlog[512];
	char cmd[1024];
	char log[512];
	char lognr[8192];
	memset(&stdlog,0,512);
	memset(&errlog,0,512);
	memset(&cmd,0,1024);
	memset(&log,0,512);
	memset(&lognr,0,8192);
	sprintf(stdlog,"%s/data/stdlog.log\0",get_current_dir_name());
	sprintf(errlog,"%s/data/errlog.log\0",get_current_dir_name());
	sprintf(log,"%s/data/accelog.log\0",get_current_dir_name());
	sprintf(cmd,"ls / 1>>%s 2>>%s",stdlog,errlog);

	if ((server_sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		fprintf(stderr,"ERROR:[socket] %s\n",strerror(errno));
		return -1;
	}
	if (bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) != 0) {
		fprintf(stderr,"ERROR:[bind] %s\n",strerror(errno));
		return -2;
	}
	if (listen(server_sockfd,100) != 0) {
		fprintf(stderr,"ERROR:[listen] %s\n",strerror(errno));
		return -3;
	}
	while (1) {
		socklen_t cli_addrsize=sizeof(client_addr);
		if ((client_sockfd = (accept(server_sockfd,(struct sockaddr *)&client_addr,&cli_addrsize))) == -1) {
			fprintf(stderr,"ERROR:[accept] %s\n",strerror(errno));
			return -4;
		}
		//printf("accept client %s:%d\n",inet_ntoa(client_addr.sin_addr),htons(client_addr.sin_port));
		//printf("server addres %s:%d\n",inet_ntoa(server_addr.sin_addr),htons(server_addr.sin_port));
		if (recv(client_sockfd,buff,81920,0) == -1) {
			fprintf(stderr,"ERROR:[recv] %s\n",strerror(errno));
			return -9;
		}
		sprintf(lognr,"=========================[%s]=============================\n",getnow());
		writelog(lognr,stdlog);
		writelog(lognr,errlog);
		writelog(lognr,log);
		if (system(cmd) == 0) {
			if (send(client_sockfd,printhtml(),strlen(printhtml()),0) == -1) {
                                fprintf(stderr,"ERROR:[send] %s\n",strerror(errno));
                                return -11;
                        }
		}
		else {
			if (send(client_sockfd,printerrhtml(),strlen(printerrhtml()),0) == -1) {
				fprintf(stderr,"ERROR:[send] %s\n",strerror(errno));
				return -10;
			}
		}
		writelog(lognr,stdlog);
		writelog(lognr,errlog);
		sprintf(buff1,"[%s] server addres %s:%d reload nginx!\n",getnow(),inet_ntoa(client_addr.sin_addr),htons(client_addr.sin_port));
		writelog(buff1,log);
		memset(&lognr,0,8192);
		memset(&buff,0,sizeof(8192));
		memset(&buff1,0,sizeof(8192));
		close(client_sockfd);
	}
	close(server_sockfd);
	return 0;
}
