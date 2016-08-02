#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <strings.h>
#include <sys/inotify.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX +1))
#define MAX_LINE 4096
#define MAX_QUST 8172
#define MAX_FILE 1024
int filenum;
typedef struct myfile {
	int wd;
	int type;
	char name[4096];
	FILE *fp;
} fn;
struct myfile filelist[MAX_FILE];
int inotifyFd,fd;
void http_head(int i,char *buf) {
        char *a="POST /test/type1/ HTTP/1.1\r\n"
                "User-Agent: Mytaill/1.0.0\r\n"
                "Host: localhost:9200\r\n"
                "Accept: */*\r\n"
        	"Content-Length: ";
        char *c="\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n";
        sprintf(buf,"%s%d%s",a,i,c);
}
void logr(char *buf) {
	FILE *fp;
	char logl[MAX_QUST];
	if ((fp = fopen("./log/mytail.log","a+")) == NULL) {
		fprintf(stderr,"open log file: %s\n",strerror(errno));
	}
	time_t mytm;
	struct tm *tminfo;
	time(&mytm);
	tminfo = localtime(&mytm);
	tminfo->tm_year += 1900;
	tminfo->tm_mon++;
	sprintf(logl,"[%d-%d-%d %d:%d:%d] %s",
		tminfo->tm_year,tminfo->tm_mon,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min,tminfo->tm_sec,buf);
	if (fwrite(logl,MAX_QUST,1,fp) != 1) {
		fprintf(stderr,"write log file: %s\n",strerror(errno));
	}
}
int conn(void)
{
        int sock;
        struct sockaddr_in ser;
        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                logr("socket create error!\n");
                return -1;
        }
        memset(&ser,'\0', sizeof ser);
        ser.sin_family = AF_INET;
        ser.sin_addr.s_addr = inet_addr("127.0.0.1");
        ser.sin_port  = htons(9200);
        if (connect(sock,(struct sockaddr *) &ser,sizeof ser) < 0) {
                logr("conn error!\n");
                return -1;
        }
        return sock;
}
void sploop(char *a)
{
	int i;
	char logl[MAX_QUST];
	sprintf(logl,"\n\nsploop: %s\n",a);
	logr(logl);
	for (i=0;i<filenum; i++) {
		sprintf(logl,"name: [%s]\t\tlist: [%d]\t\twd: [%d]\t\ttype: [%d]\t\tTotal:[%d]\n",
			filelist[i].name,i,filelist[i].wd,filelist[i].type,filenum);
		logr(logl);
	}
	sprintf(logl,"sploop: %s END\n\n\n",a);
	logr(logl);
}
void gettm(char *stm)
{
	time_t mytm;
	struct tm *tminfo;
	time(&mytm);
	tminfo = localtime(&mytm);
	tminfo->tm_year += 1900;
	tminfo->tm_mon++;
	sprintf(stm,"\t\"datetime\":\"%d-%02d-%02d %02d:%02d:%02d\",\n\t\"timestmap\":\"%d\"",
		tminfo->tm_year,tminfo->tm_mon,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min,tminfo->tm_sec,mytm);
}
// no userd by findname()
char *findname(char *s, char *sech) {
	char *p = s,*d = NULL;
	size_t len = strlen(sech);
	for (; (p=strchr(p,*sech))!=0;p++) {
		if(strncmp(p,sech,len)==0)
			d = p;
	}
	return d;
}
int sockw(char *buf) {
        return write(fd,buf,strlen(buf));
}
int sockr(char *buf) {
        int i;
	char logl[MAX_QUST];
        //memset(buf,'\0',MAX_QUST);
        if ((i = read(fd,buf,MAX_QUST)) == -1)  {
        /*if ((i = read(fd,buf,MAX_QUST)) != -1)  {
                sprintf(logl,"RECV:\n%s\nRECV_END\n",buf);
		logr(logl);
	}
        else {*/
                sprintf(logl,"sockr in fd %d read Error!\n",fd);
		logr(logl);
	}
        return i;
}
void my_getline(struct myfile file) {
	char line[MAX_LINE];
	char content[MAX_LINE];
	char tim[54];
	char qust[MAX_QUST];
	char logl[MAX_QUST];
	while (fgets(line,MAX_LINE, file.fp) != NULL) {
		line[strlen(line)-1]='\0';
		gettm(tim);
		sprintf(content,"{\n\t\"filename\":\"%s\",\n%s,\n\t\"content\":\"%s\"\n}\n",file.name,tim,line);
		http_head(strlen(content),line);
		sprintf(qust,"%s%s",line,content);
		//printf("%s",qust);
		if (sockw(qust) == -1) {
			sprintf(logl,"send message ERROR: %s\n",qust);
			logr(logl);
		}
		if (sockr(qust) == -1) 
			logr("recv message ERROR\n");
	}
}

void my_die(struct inotify_event *i)
{
	int x,y=0,wd,stat=0;
	char filepath[1024];
	char logl[MAX_QUST];
	memset(filepath, '\0', 1024);
	if (i->mask & IN_DELETE||i->mask & IN_MOVED_FROM) {
		//sploop("delete start");
		for (x=0; x<filenum; x++) {
			if (filelist[x].wd == i->wd) {
				sprintf(filepath,"%s%s",filelist[x].name,i->name);
				break;
			}
		}
		for (y=0; y<filenum; y++) {
			if (strcmp(filelist[y].name,filepath) == 0 && filelist[y].type != 0) {
				sprintf(logl,"DELETE filename=[%s] path=[%s] wd=[%d] list=[%d]\n",
						filelist[y].name,filepath,filelist[y].wd,y);
				logr(logl);
				if (inotify_rm_watch(inotifyFd, filelist[y].wd) != 0) {
                                       sprintf(logl,"ERROR: [rm %d] %s\n",i->wd,strerror(errno));
					logr(logl);
				}
                                else {
                                        sprintf(logl,"wd %d be removed!\n",filelist[y].wd);
					logr(logl);
				}
				fclose(filelist[y].fp);
				for (x=y; x < filenum; x++) {
                                	filelist[x].wd = filelist[x+1].wd;
                                	filelist[x].fp = filelist[x+1].fp;
                                	strcpy(filelist[x].name, filelist[x+1].name);
                        	}
				filenum--;
				break;
			}
		}
		//sploop("delete stop");
	} 
	if (i->mask & IN_CREATE) {
addfile:
		//sploop("create start");
		for (x=0;x<filenum;x++) {
			if (i->wd == filelist[x].wd) {
				sprintf(filepath,"%s%s",filelist[x].name,i->name);
				break;
			}
		}
		for (x=0;x<filenum;x++) {
			if (strcmp(filepath,filelist[x].name) == 0) {
				my_getline(filelist[x]);
                                return;
                        }
		}
		if ((wd = inotify_add_watch(inotifyFd,filepath,IN_MODIFY)) == -1) {
                        sprintf(logl,"inotify_add_watch ERROR: [%s][%s] !\n",strerror(errno),filepath);
			logr(logl);
                        exit(-2);
                }
                sprintf(logl,"ADD file wd = [%d]: %s\n", wd, filepath);
		logr(logl);
                filelist[filenum].wd = wd;
                filelist[filenum].type = 1;
                strcpy(filelist[filenum].name,filepath);
                filelist[filenum].fp=fopen(filepath,"r");
                if (filelist[filenum].fp == NULL) {
                        sprintf(logl,"open file %s error [%s]\n",filepath,strerror(errno));
			logr(logl);
		}
                my_getline(filelist[filenum]);
		filenum++;
		//sploop("create end");
	} 
	if (i->mask & IN_MODIFY) {
		for (x=0; x<filenum; x++) {
			if (filelist[x].wd == i->wd && filelist[x].type == 1) {
				my_getline(filelist[x]);
				stat = 1;
				break;
			} 
			else if (strcmp(filelist[x].name,filepath) == 0 && filelist[x].type == 1) {
				my_getline(filelist[x]);
				stat = 1;
                                break;
			} 
		}
		if (stat == 0) {
			goto addfile;
		}
	}
}

int main(int argc, char **argv)
{
	if (fork() != 0)
		return 0;
	int wd,j;
	char buf[BUF_LEN];
	char logl[MAX_QUST];
	ssize_t numRead;
	char *p;
	struct inotify_event *event;
	filenum = argc-1;
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		logr("show this help messages!\n");
		return -1;
	}
	if ((inotifyFd = inotify_init()) == -1) {
                logr("inotify_init ERROR!\n");
                exit(-1);
        }
	if ((fd = conn()) < 0) {
		logr("IN MAIN: connent ERROR\n");
		return fd;
	}
	for (j = 0; j < filenum; j++) {
                if ((wd = inotify_add_watch(inotifyFd,argv[j+1],IN_MODIFY|IN_DELETE|IN_MOVED_FROM)) == -1) {
                        logr("inotify_add_watch ERROR!\n");
                        exit(-2);
                }
		//printf("wd = [%d]: %s\n", wd, argv[j+1]);
                filelist[j].wd = wd;
                filelist[j].type = 0;
                strcpy(filelist[j].name,argv[j+1]);
                filelist[j].fp=fopen(argv[j+1],"r");
                if (filelist[j].fp == NULL) {
                        sprintf(logl,"open file %s error [%s]\n",argv[j+1],strerror(errno));
			logr(logl);
		}
                my_getline(filelist[j]);
        }
	for (;;) {
		if ((numRead = read(inotifyFd,buf,BUF_LEN)) == 0) 
			logr("read from inotify fd return 0!\n");
		if (numRead == -1) {
			logr("read from inotify fd ERROR!\n");
			return -3;
		}
		for (p = buf; p<buf+numRead;) {
			event = (struct inotify_event *)p;
			my_die(event);
			p += sizeof(struct inotify_event) + event->len;
		}
	}
	return 0;
}
