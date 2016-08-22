#include <stdio.h>
main()
{
	int a = 5;
	int i;
	for (i = 0; i < 64; i++)
		printf("JG = %d|a = %d|i = %d\n", a & i, a, i);
}
