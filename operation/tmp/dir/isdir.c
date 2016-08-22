#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
 struct stat st;
 printf("%s",argv[1]);
 stat(argv[1],&st);
 if (S_ISDIR(st.st_mode))
  printf("is a dir\n");
 else
  printf("is not a dir\n");
 return 0;
}
