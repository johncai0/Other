#include <stdio.h>
#include <string.h>

char *foo()
{
    static char str[32] = "1234567890";
    fprintf(stdout, "[1][%s][%p]\n", str, &str);

    char *_str = str;
    return _str;
}

int main()
{

    char *str = foo();
    fprintf(stdout, "[2][%s][%p]\n", str, str);

    char buffer[32];
    memset(buffer, 0, 32);
    fprintf(stdout, "[3][%s][%p]\n", str, buffer);

    static char arr1[32];
    static char arr2[32] = "abc";
    char arr3[32] = "abc";
    fprintf(stdout, "[arr1][%p]\n", arr1);
    fprintf(stdout, "[arr2][%p]\n", arr2);
    fprintf(stdout, "[arr3][%p]\n", arr3);

    return 0;
}

