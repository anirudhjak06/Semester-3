//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct dynamic
{
    int lead;
    struct dynamic *after;
}Dynamic_data;

Dynamic_data *CreateNode(int lead)
{
    Dynamic_data *obj = (Dynamic_data*)malloc(sizeof(Dynamic_data));
    obj->lead=lead;
    obj->after=NULL;
    return obj;
}

void Joining(Dynamic_data *bag[],int latest,int instant,int lead)
{
    bag[latest] = CreateNode(lead);
    bag[latest]->after = bag[instant];
}

Dynamic_data *Pushing(Dynamic_data *bag,int lead)
{
    if(bag==NULL)
    {
        return CreateNode(lead);
    }
    else
    {
        Dynamic_data *instant = CreateNode(lead);
        instant->after=bag;
        return instant;
    }
}

int Least(int p,int q)
{
    if(p==-1)
    {
        return q;
    }    
    if(p<=q)
    {
        return p;
    }
    else
    { 
        return q;
    }   
}

void Mark_elements(Dynamic_data *elements)
{
    if(elements!=NULL)
    {
        Mark_elements(elements->after);
        printf("%d ",elements->lead);
        //i++;
    }  
}

void Classification(int size,int money[],int x)
{
    int digit[size],least=-1;
    //int i=0;
    Dynamic_data *elements[size];
    for(int index=0;index<size;index++)
    {
        elements[index]=NULL;
    }
    for(int b=size-1;b>=0;b--)
    {
        int y = x,compute=0;;
        for(int a=b;a>=0;a--)
        {
            while(y>=money[a])
            {
                y-= money[a];
                compute++;
                elements[b]=Pushing(elements[b],money[a]);
            }
        }
        digit[b]=compute;
        if(least==-1)
        {
            least = b;
        }
        else if(digit[least] > digit[b])
        {
            least = b; 
        }   
    }
    //printf("Output for Test Case (%d) ",i);
    Mark_elements(elements[least]);
}

void Travel_Stay_Administrator(int price[],int size)
{
    int x[size+1];
    Dynamic_data *elements[size+1];
    for(int j=0;j<size+1;j++)
    {
        elements[j]=NULL;
        x[j]=-1;
    }
    x[0]=0;
    for(int a=1;a<size+1;a++)
    {
        for(int b=0;b<a;b++)
        {
            if(price[a]-price[b]<=20)
            {
                int h = x[a];
                x[a]=Least(x[a],x[b]+(20-(price[a]-price[b])) * (20-(price[a]-price[b]))) ;
                if(x[a]!=h && b!=0)
                {
                    Joining(elements,a,b,b);
                }
            }
        }
    }
    elements[size]=Pushing(elements[size],size);
    printf("Hotels stopped at are : ");
    Mark_elements(elements[size]);
    printf("\nTotal Penalty : ");
    printf("%d\n",x[size]);

}

void main()
{
    char name[100];
    int size;
    FILE* file_pr;
    printf("\n-----------------------------------\n");
    printf("Problem (i) : Coin Classification ");
    printf("\n-----------------------------------\n");
    printf("Enter the File Name : ");
    scanf("%s",name);
    file_pr= fopen(name,"r");
    fscanf(file_pr,"%d",&size);
    int money[size],k,x;
    for(int loop=0;loop<size;loop++)
    {
        fscanf(file_pr,"%d",&money[loop]);
    }
    fscanf(file_pr,"%d",&k);
    for(int counter=0;counter<k;counter++)
    {
        fscanf(file_pr,"%d",&x);
        printf("Output for Test Case (%d) : ",(counter+1));
        Classification(size,money,x);
        printf("\n");
    }
    fclose(file_pr);
    printf("\n----------------------------------------\n");
    printf("Problem (ii) : Travel and Stay Planner");
    printf("\n----------------------------------------\n");
    printf("Enter the File Name : ");
    scanf("%s",name);
    file_pr = fopen(name,"r");
    fscanf(file_pr,"%d",&size);
    int price[size+1];
    price[0]=0;
    for(int j=1;j<=size;j++)
    {
        fscanf(file_pr,"%d",&price[j]);
    }
    Travel_Stay_Administrator(price,size);
    fclose(file_pr);
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
}