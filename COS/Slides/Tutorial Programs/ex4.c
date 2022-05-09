#include <stdio.h>
#include <stdlib.h>
#include <string.h>
size_t strlonger(char *s,char *t)
{
    return (strlen(s)-strlen(t));
}
int main()
{
    size_t a=20;
    size_t result=strlonger("cos","semTwo");
    printf("%zu\n",result);
    printf("%zu\n",a);
    
}