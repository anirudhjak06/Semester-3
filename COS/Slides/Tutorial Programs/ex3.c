#include<stdio.h>

float sum_elements(float a[],unsigned length)
{
    int i;
    float r=0;
    for(i=0;i<=length-1;i++)
        r=r+a[i];
    return r;

}


int main()
{
    float k;
    float a[0]={4};
    k=sum_elements(a,5);
    printf("%f",k);
}