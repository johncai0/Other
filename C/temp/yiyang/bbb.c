
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


	char helo[] ="POST /seo_chklogin2.asp HTTP/1.1\r\nAccept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, */*\r\nReferer: http://shouquan.taobaoyiyang.com/seo_dl0720.asp\r\nAccept-Language: zh-cn\r\nContent-Type: application/x-www-form-urlencodedr\nAccept-Encoding: gzip, deflate\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729)\r\nHost: shouquan.taobaoyiyang.com\r\nContent-Length: 121\r\nConnection: Keep-Alive\r\nCache-Control: no-cache\r\nCookie: CNZZDATA1253195915=1491310970-1413790564-http%253A%252F%252Fshouquan.taobaoyiyang.com%252F%7C1415151933\r\n\r\nuserqq=13704142751111&userpwd=78952130&mid=%7BC0D05949-62B0-4D32-9D1C-5C1EC2981E95%7D&buildver=40.283&submit=%CC%A1%3F%3F\r\n\r\n";
	//char helo[] ="GET /seo_dl0720.asp HTTP/1.1\r\nAccept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, */*\r\nAccept-Language: zh-CN\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)\r\nAccept-Encoding: gzip, deflate\r\nHost: shouquan.taobaoyiyang.com\r\nConnection: Keep-Alive\r\nCookie: safedog-flow-item=64D20DFC24E8128ADC88B664CA4CD7EE; CNZZDATA1253195915=972419444-1413246354-http%253A%252F%252Fshouquan.taobaoyiyang.com%252F%7C1415113815\r\n\r\n";
	printf("%s\n",helo);
	write(sockfd, helo, strlen(helo));

	char buffer[4096] = {0};
	size_t size = read(sockfd, buffer, sizeof(buffer));
	write(1, buffer, sizeof(buffer));

	close(sockfd);

	return 0;
}
