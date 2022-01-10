#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strlonger(char* a,char* b){
    unsigned long int c = strlen(a);
    unsigned long int d = strlen(b);
    printf("%uld\n",strlen(a));
    printf("%uld\n",strlen(b));
    return (c-d)>0;
}
int main(int argc, const char * argv[]) {
    
    //float a[]={1.234,3.4543,456.634,456,234};
    //float a[]={};
    //printf("%f\n",sum_elements(a, 0));
    
    char a[5]="abcde";
    char b[5]="abcde";
    
    printf("%d\n",strlonger(a,b));
    
    return 0;
}