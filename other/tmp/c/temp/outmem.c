#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc,char **argv)
{
	while ( 1 ) {
		malloc(1024000);
		usleep(100);
	}
	return 0;
}
