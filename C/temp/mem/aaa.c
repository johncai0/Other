#include <stdio.h>
extern  double get_mem();
main()
{
	double c = get_mem();
	printf("%0.2f\n",c);
}
double get_mem()
{
        FILE *fp;
        char buf[512];
        int i;
        int total, free, cache;
        double t;
        if ((fp=fopen("/proc/meminfo","r")) == NULL)
        {
                fprintf(stderr,"ERROR: Open meminfo ERROR!");
                return -8;
        }
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"MemTotal: %d kB", &total);
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"MemFree: %d kB", &free);
        fgets(buf,sizeof(buf),fp);
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"Cached: %d kB", &cache);
        t = (double)((double)(total - (cache + free)) / (double)(total) * 100);
	printf("%0.2f\n",t);
        return t;
}
