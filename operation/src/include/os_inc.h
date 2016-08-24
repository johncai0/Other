#include <stdio.h>

//net
#include <sys/types.h>
#include <sys/socket.h>

//net type
#include <netinet/in.h>
#include <arpa/inet.h>

//errno
#include <errno.h>
#include <string.h>

//exit
#include <unistd.h>
#include <stdlib.h> //atoi

//epoll
#include <sys/epoll.h>

//file or directory
#include <sys/stat.h>
#include <dirent.h>
