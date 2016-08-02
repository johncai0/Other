#include <stdio.h>
#include <limits.h>
#include <strings.h>
#include <sys/inotify.h>
#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX +1))
#define MAX_LINE 4096
void die(struct inotify_event *i)
{
	printf("\twd=%2d; ", i->wd);
	if (i->cookie > 0)
		printf("cookie = %4d; ",i->cookie);
	printf("mask = ");
	if (i->mask & IN_ACCESS)	printf("read access");
	if (i->mask & IN_ATTRIB)	printf("data chaged");
	if (i->mask & IN_CLOSE_NOWRITE)	printf("close read_olny open");
	if (i->mask & IN_CLOSE_WRITE)	printf("close write open");
	if (i->mask & IN_CREATE)	printf("in montor dir create file/dir %d", i->mask);
	if (i->mask & IN_DELETE)	printf("in montor dir delete file/dir %d", i->mask);
	if (i->mask & IN_DELETE_SELF)	printf("delete montor dir self");
	if (i->mask & IN_IGNORED)	printf("removed whith kernel or app");
	if (i->mask & IN_ISDIR)		printf("name include path");
	if (i->mask & IN_MODIFY)	printf("file be updated");
	if (i->mask & IN_MOVE_SELF)	printf("remove self");
	if (i->mask & IN_MOVED_FROM)	printf("file remove to out");
	if (i->mask & IN_MOVED_TO)	printf("file remove to in");
	if (i->mask & IN_OPEN)		printf("file be open");
	if (i->mask & IN_Q_OVERFLOW)	printf("event out of queue");
	if (i->mask & IN_UNMOUNT)	printf("unmount of this dir on file system");
	printf(" \n");
	if (i->len > 0)
		printf("\tname = [%s]\n", i->name);
}

char *__getline(FILE *fp,char *line) {
	return fgets(line,MAX_LINE, fp);
}

void my_die(struct inotify_event *i)
{
        printf("\twd=%2d; ", i->wd);
        if (i->cookie > 0)
                printf("cookie = %4d; ",i->cookie);
        printf("mask = ");
        if (i->mask & IN_ATTRIB)        printf("data chaged");
        if (i->mask & IN_DELETE_SELF)   printf("delete montor dir self");
        if (i->mask & IN_MODIFY)        printf("file be updated");
        if (i->mask & IN_MOVE_SELF)     printf("remove self");
        printf(" \n");
        if (i->len > 0)
                printf("\tname = [%s]\n", i->name);
}

int main(int argc, char **argv)
{
	int inotifyFd,wd,j;
	char buf[BUF_LEN];
	ssize_t numRead;
	char *p;
	struct inotify_event *event;
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		printf("show this help messages!\n");
	if ((inotifyFd = inotify_init()) == -1) {
		printf("inotify_init ERROR!\n");
		return -1;
	}
	for (j = 1; j < argc; j++) {
		if ((wd = inotify_add_watch(inotifyFd,argv[j],IN_ALL_EVENTS)) == -1) {
			printf("inotify_add_watch ERROR!\n");
			return -2;
		}
		printf("Watching %s using wd %d\n", argv[j],wd);
	}
	for (;;) {
		if ((numRead = read(inotifyFd,buf,BUF_LEN)) == 0) 
			printf("read from inotify fd return 0!\n");
		if (numRead == -1) {
			printf("read from inotify fd ERROR!\n");
			return -3;
		}
		printf("Read %ld bytes from inotify fd\n",(long)numRead);
		for (p = buf; p<buf+numRead;) {
			event = (struct inotify_event *)p;
			die(event);
			p += sizeof(struct inotify_event) + event->len;
		}
	}
	return 0;
}
