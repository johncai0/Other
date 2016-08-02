#include <stdio.h>
#include <string.h>
main()
{
	char *a = "wokao\0";
	//a[strlen(a)+1] = '\0';
	char *b = a;
	while (*a != '\0') {
		printf("%c,",*a);
		a++;
	}
	printf("\n%d %d\n",strlen(b),sizeof b);
}
