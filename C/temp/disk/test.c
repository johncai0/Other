#include <sys/statfs.h>
#include <stdio.h>
main()
{
unsigned long long freeDisk = 0;
size_t mbFreedisk = 0;
unsigned long long totalDisk = 0;
size_t mbTotalsize = 0;

struct statfs diskInfo;

statfs("/", &diskInfo);    

freeDisk = (unsigned long long)(diskInfo.f_bfree) * (unsigned long long)(diskInfo.f_bsize);

mbFreedisk = freeDisk >> 20;

totalDisk = (unsigned long long)(diskInfo.f_blocks) * (unsigned long long)(diskInfo.f_bsize);
mbTotalsize = totalDisk >> 20;    

printf ("/mnt/sdcard  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);


statfs("/cache", &diskInfo);

freeDisk = (unsigned long long)(diskInfo.f_bfree) * (unsigned long long)(diskInfo.f_bsize);
mbFreedisk = freeDisk >> 20;

totalDisk = (unsigned long long)(diskInfo.f_blocks) * (unsigned long long)(diskInfo.f_bsize);
mbTotalsize = totalDisk >> 20;


printf ("/cache  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);
}
