#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc,char **argv) {
	char *path=".";
	DIR *dir;
	struct dirent *ptr;
	if (argv[1])
		dir = opendir(argv[1]);
	else
		dir = opendir(path);
	while ((ptr  = readdir(dir)) != NULL) {
		printf("d_name: %s\n",ptr->d_name);
	}
	closedir(dir);
	return 0;
}
