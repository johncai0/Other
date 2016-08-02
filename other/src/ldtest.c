#include <stdio.h>
#include <dlfcn.h>

int main(void)
{
	int a=8,b=3;
	void (*c)(void);
	void *d = dlopen("./lib/libfirst_so.so",RTLD_LAZY);
	*(void **) (&c) = dlsym(d,"vd");
	(*c)();
	fprintf(stderr,"Open DL: %s\n",dlerror());
	int (*e)(int,int);
	e = dlsym(d,"ajb");
	fprintf(stdout,"in fun += %d\n",(*e)(a,b));
	dlclose(d);
}
