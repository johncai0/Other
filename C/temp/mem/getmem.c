#include <stdio.h>
main()
{
	FILE *fp;
	char buf[512];
	int i;
	long long int total, free, cache;
	long double t;
	if ((fp=fopen("/proc/meminfo","r")) == NULL)
	{
		fprintf(stderr,"ERROR: Open meminfo ERROR!");
		return -8;
	}
	fgets(buf,sizeof(buf),fp);
	sscanf(buf,"MemTotal: %lld kB", &total);
	//printf("%s %d\n",buf,total);
	fgets(buf,sizeof(buf),fp);
	//printf("%s",buf);
	sscanf(buf,"MemFree: %lld kB", &free);
	fgets(buf,sizeof(buf),fp);
	fgets(buf,sizeof(buf),fp);
	//printf("%s",buf);
	sscanf(buf,"Cached: %lld kB", &cache);
	fprintf(stdout,"Total: %lld\tFree: %lld\tCache: %lld\t\n",total, free, cache);
	t = ((long double)(total) - ((long double)(cache) + (long double)(free))) / (long double)(total) * 100;
	fprintf(stdout,"bili(%): %0.2llf\n",t);
	return 0;
}
