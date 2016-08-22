#include <stdio.h>
void bin_print(int n)
 {

     int i;
     for (i = 31; i >=0; i--)
         fprintf(stdout, "%d", n & (1 << i) ? 1 : 0);
     fprintf(stdout, "\n");
 }
main()
{
	long int i=1024;
	long int a,b,c,d,e,f,g;
	bin_print(i);
	bin_print(4);
	fprintf(stdout,"i = %ld\n",i);
	a = i >> 4; fprintf(stdout,"i >> = %ld\n",a); bin_print(a);
	b = i << 4; fprintf(stdout,"i << = %ld\n",b); bin_print(b);
	c = i & 4; fprintf(stdout,"i & = %ld\n",c); bin_print(c);
	d = i | 4; fprintf(stdout,"i | = %ld\n",d); bin_print(d);
	e = ~ i; fprintf(stdout,"i ~ = %ld\n",e); bin_print(e);
	f = i ^ 4; fprintf(stdout,"i ^ = %ld\n",f); bin_print(f);
	g = 1028 & 4; fprintf(stdout,"10 & 4 = %ld\n",g); bin_print(g);
}
