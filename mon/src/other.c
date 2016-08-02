#include "mon.h"
int equs(char *d, char *s)
{
	int i,len;
	char *dest=d,*src=s,*init=d;
	for (len=0;*init++;len++)
		;
	for (i=0; *dest && *src && *dest == *src; i++) {
		dest++;
		src++;
	}
	if (*dest || i<len) {
		return 0;
	} else {
		return i;
	}
}
