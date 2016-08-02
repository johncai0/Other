#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFSIZE 8192

void http_head(char *buf) {
	char *a="POST /test/type1/ HTTP/1.1\r\n"
		"User-Agent: Mytaill/1.0.0\r\n"
		"Host: localhost:9200\r\n"
		"Accept: */*\r\n"
		"Content-Length: ";
	char *c="\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n";
	char *d="{\n"
		"\n\t\"filename\":\"tmp/c.txt\","
		"\n\t\"datetime\":\"2016-04-08 12:17:16\","
		"\n\t\"timestmap\":\"1460089036\","
		"\n\t\"content\":\"aaaaaaaaaaaaaaa\""
		"\n}";

	sprintf(buf,"%s%d%s%s",a,strlen(d),c,d);
	printf("%s\n",buf);
}
int conn(void)
{
	int sock;
	struct sockaddr_in ser;
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("socket create error!\n");
		return -1;
	}
	memset(&ser,'\0', sizeof ser);
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");
	ser.sin_port  = htons(9200);
	if (connect(sock,(struct sockaddr *) &ser,sizeof ser) < 0) {
		printf("conn error!\n");
		return -1;
	}
	return sock;
}
int sockw(int fd) {
	char buf[BUFSIZE];
	/*char *l = "my test data";
	char *f = "/tmp/aaa.txt";
	sprintf(buf,"%s{\n   \"filename\":\"%s\",\n   \"content\":\"%s\"\n}\n",http_head(),l,f);
	printf("%s\n",buf);
	return write(fd,buf,strlen(buf));
	strcpy(buf,http_head());*/
	http_head(buf);
	return write(fd,buf,strlen(buf));
}
int sockr(int fd) {
	int i;
	char buf[BUFSIZE];
	memset(buf,'\0',sizeof buf);
	//if ((i = read(fd,buf,sizeof buf)) == -1) 
	if ((i = read(fd,buf,sizeof buf)) != -1) 
		printf("RECV:\n%s\nRECV_END\n",buf);
	else
		printf("in fd %d read Error!\n",fd);
	return i;
}
int main(void) {
	int fd,i;
	if ((fd = conn()) < 0) {
		printf("conn Error!\n");
		return fd;
	}
//	for (i = 0; i <= 200000; i++) {
//		if (i%200 == 0)
			printf("Insert into [%d] data!\n",i);
		if (sockw(fd) == -1) {
			printf("sock write Error\n");
			return -1;
		}
		if (sockr(fd) == -1) {
			printf("sock read Error\n");
			return -1;
		}
//	}
	close(fd);
	return 0;
}
