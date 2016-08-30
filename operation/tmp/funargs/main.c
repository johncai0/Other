#include <stdio.h>
void john(int *c) {
	*c=6;
}
int main (int argc, char **argv) {
	int a=3, b=4;
	int c=-1;
	john(&c);
	fprintf(stdout,"c = %d\n",c);
}
