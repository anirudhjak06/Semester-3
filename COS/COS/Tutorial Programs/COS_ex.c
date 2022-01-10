#include<stdio.h>

long plus(long x,long Y);

void sumstore(long x,long y,long *dest)
{
    long t=plus(x,y);
    *dest=t;
}


