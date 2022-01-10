#include<stdio.h>
#include<stdlib.h>

float sum_elements(float a[],unsigned length)
{
    float result=0;
    printf("\nLength=%u\nLenght-1=%u\n",length,length-1);
    for(int i=0;i<length;i++)
    {
        result=result+a[i];
    }
    return result;
}

int main()
{
    float r;
    int n;
    scanf("%d",&n);
    //int length=5;
    float a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",&a[i]);
    }
    r=sum_elements(a,n);
    printf("%f \n",r);
}