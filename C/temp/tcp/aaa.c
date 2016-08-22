
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("42.121.113.148");
	//addr.sin_addr.s_addr=inet_addr("188.188.3.240");
	//addr.sin_port=htons(1111);
	addr.sin_port=htons(80);
	if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0) {
		fprintf(stderr, "connect fat!\n");
		return -4;
	}


	char helo[] ="GET /seo_dl0720.asp HTTP/1.1\r\nAccept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, */*\r\nAccept-Language: zh-CN\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)\r\nAccept-Encoding: gzip, deflate\r\nHost: shouquan.taobaoyiyang.com\r\nConnection: Keep-Alive\r\nCookie: safedog-flow-item=64D20DFC24E8128ADC88B664CA4CD7EE\r\n\r\n";
	//char helo[] ="GET /seo_dl0720.asp HTTP/1.1\r\nAccept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, */*\r\nAccept-Language: zh-CN\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)\r\nAccept-Encoding: gzip, deflate\r\nHost: shouquan.taobaoyiyang.com\r\nConnection: Keep-Alive\r\nCookie: safedog-flow-item=64D20DFC24E8128ADC88B664CA4CD7EE; CNZZDATA1253195915=972419444-1413246354-http%253A%252F%252Fshouquan.taobaoyiyang.com%252F%7C1415113815\r\n\r\n";
	printf("%s\n",helo);
	write(sockfd, helo, strlen(helo));

	char buffer[4096] = {0};
	size_t size = read(sockfd, buffer, sizeof(buffer));
	write(1, buffer, sizeof(buffer));

	close(sockfd);

	return 0;
}
