#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
char *strfin(char *sc, char *dc);

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
	char strings[]="HTTP/1.1 200 OK\r\nDate: Thu, 06 Nov 2014 02:20:13 GMT\r\nServer: Microsoft-IIS/6.0\r\nX-Powered-By: ASP.NET\r\nContent-Length: 707\r\nContent-Type: text/html\r\nSet-Cookie: ASPSESSIONIDCAQRSRAR=OBJEKMKAPDDKAGFCPOMDIPDP; path=/\r\nCache-control: private\r\n\r\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n<head>\r\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n<title>登录</title>\r\n</head>\r\n<body>\r\n<form id=\"login-form\" name=\"login-form\" method=\"post\" action=\"seo_chklogin2.asp\">\r\n<input type=\"text\" name=\"userqq\" id=\"userqq\" value=\"\" /><br />\r\n<input type=\"text\" name=\"userpwd\" id=\"userpwd\" value=\"\" /><br />\r\n<input type=\"text\" name=\"mid\" id=\"mid\" value=\"\" /><br />\r\n<input type=\"text\" name=\"buildver\" id=\"buildver\" value="" /> <br />\r\n<input type=\"submit\" name=\"submit\" value=\"test\" >\r\n</form>\r\n</body>\r\n</html>\r\n\r\n";
	char sess[]="HTTP/1.1 200 OK\r\nDate: Thu, 06 Nov 2014 02:20:13 GMT\r\nServer: Microsoft-IIS/6.0\r\nX-Powered-By: ASP.NET\r\nContent-Length: 707\r\nContent-Type: text/html\r\nSet-Cookie: ASPSESSIONIDCAQRSRAR=OBJEKMKAPDDKAGFCPOMDIPDP; path=/\r\nCache-control: private\r\n\r\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\"><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /></head><body><div id=\"loginresult\">43608f7d793f84ae0ddd6beafb9716a4</div><div id=\"errmsg\"></div></body></html>";
	//char strings[]="HTTP/1.1 200 OK\r\nServer: MyServer1.2\r\nSD: This's A Test Web Server!!!\r\n\r\n<html><head><title>TEST</title></head><body><h3>Hello word!!!</h3></body></html>";
	char buffer[1024];
	//---------------------------
	//struct sockaddr *peersa;
	unsigned int len=sizeof(caddr);
	char *checklong = "POST /seo_chklogin2.asp";
	char *checkconn = "POST ";
	//---------------------------
	for (;;) {
		int connfd=accept(listenfd, NULL, NULL);
		//int connfd=accept(listenfd, (struct sockaddr *) &caddr, &len);
		//int connfd=accept(listenfd, (struct sockaddr)caddr, &peerlen);
	//	fprintf(stdout,"IP: %s\nPort: %d\n", inet_ntop(AF_INET, &caddr.sin_addr, buff,sizeof(buff)),ntohs(caddr.sin_port));
		bzero(buffer,sizeof(buffer));
		read(connfd, buffer, sizeof(buffer));
		fprintf(stdout,"Client's Return: \"%s\"\n",buffer);
		if (strfin(buffer,checklong))
			write(connfd, sess,strlen(sess));
		else 
			write(connfd, strings,strlen(strings));
		//read(connfd,buffer,sizeof(buffer));
		//fprintf(stdout,"%s",buffer);
		close(connfd);
	}
}
char *strfin(char *sc, char *dc)  
{  
    char *fs = sc, *fd = dc;  
    char *dffs, *dffd;  
    int i, j = 0;  
    for (i = 0; *fd; fd++)  
        i++;  
    fd -= i; j = i;  
    for (; *fs; fs++) {  
        if (*fs == *fd) {  
            dffs = fs; dffd = fd;  
            while (*++dffs == *++dffd && *dffs && --j) ;  
            if (j == 1)  
                return fs;  
            else   
                j = i;  
        }  
    }  
    return (0);  
}
