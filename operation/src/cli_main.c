#include "include/os_inc.h"
#include "include/operation_inc.h"
void cli_help() {
	fprintf(stdout,"\targv[1]:/path/to/upload.conf\n");
	fprintf(stdout,"eg:\n");
	fprintf(stdout,"\t/path/to/cli /path/to/upload.conf\n");
}
int main(int argc, char **argv) {
	if (argc < 1) {
		cli_help();
		return -1;
	}
	/*if ((sockfd=connect_ser(argv[1],atoi(argv[2]))) == -1) {
		fprintf(stderr,"connect to server %s:%s Error!\n",argv[1],argv[2]);
		return -1;
	} else {
		fprintf(stdout,"Connect Success!\n");
		close(sockfd);
	}*/
	if (readconf(argv[1]) != 0) {
		fprintf(stdout,"Error: Read config ERROR!\n");
	}
	return 0;
}
