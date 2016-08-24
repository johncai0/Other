#include "include/os_inc.h"
#include "include/operation_inc.h"
int connect_ser(char *ip, int port) {
        int sockfd=-1;
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                fprintf(stderr,"connect_ser.socket[ERROR]: %s!\n",strerror(errno));
                return -1;
        }
        struct sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=inet_addr(ip);
        addr.sin_port=htons(port);
        if (connect(sockfd,(struct sockaddr *)&addr, sizeof(struct sockaddr_in)) !=0) {
                fprintf(stderr,"connect_ser.connect[ERROR]: %s:%d %s!\n",ip,port,strerror(errno));
                return -1;
        }
        return sockfd;
}
