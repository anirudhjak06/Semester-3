//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct knapsack_data
{
    int lead;
    struct knapsack_data *after;
}Knapsack_data;

Knapsack_data *CreateNode(int lead)
{
    Knapsack_data *obj = (Knapsack_data*)malloc(sizeof(Knapsack_data));
    obj->lead=lead;
    obj->after=NULL;
    return obj;
}

void Joining(Knapsack_data *bag[],int latest,int instant,int lead)
{
    bag[latest] = CreateNode(lead);
    bag[latest]->after = bag[instant];
}

void Joining_for_Bounded(int n,Knapsack_data *bag[][n],int latest1,int latest2,int instant1,int instant2,int lead)
{
    if(lead==-1)
    {
        bag[latest1][latest2]=bag[instant1][instant2];   
    }
    else
    {
        bag[latest1][latest2]=CreateNode(lead);
        bag[latest1][latest2]->after = bag[instant1][instant2];   
    }
}

void mark_Knapsack(Knapsack_data *bag[],int index)
{
    Knapsack_data *pre = bag[index];
    while(pre!=NULL)
    {
        printf("%d ",pre->lead);
        pre=pre->after;
    }
    printf("\n");  
}

void Bounded_mark_Knapsack(int k,Knapsack_data *bag[][k],int index,int m)
{
    Knapsack_data *pre = bag[index][m];
    while(pre!=NULL)
    {
        printf("%d ",pre->lead);
        pre=pre->after;
    }
    printf("\n"); 
}

int Highest(int p,int q)
{
    if(p>=q)
    {
        return p;
    }
    else
    { 
        return q;
    }   
}

void Knapsack_for_Unbounded(int k,int hh,int load[],int price[])
{
    int pouch[hh+1];
    Knapsack_data *bag[hh+1];
    pouch[0]=0;
    for(int j=0;j<hh+1;j++)
    {
        bag[j]=NULL;
    }
    for(int l=1;l<=hh;l++)
    {
        pouch[l]=0;
        for(int m=0;m<k;m++)
        {
            if(load[m]<=l)
            {
                int p = pouch[l];
                pouch[l]=Highest(pouch[l],pouch[l-load[m]]+price[m]);
                if(pouch[l]!=p)
                {
                    Joining(bag,l,l-load[m],m+1);
                }
            }
        }
    }
    printf("The value of the objects in Unbounded Knapsack for the given weight is : %d\n",pouch[hh]);
    printf("Objects in the Unbounded Knapsack are : ");
    mark_Knapsack(bag,hh);
}

void KnapSack_for_Bounded(int k,int hh,int load[],int cost[])
{
    int pouch[hh+1][k+1];
    for(int y=0;y<=hh;y++)
    {
        pouch[y][0]=0;
    }
    for(int q=0;q<=k;q++)
    {
        pouch[0][q]=0;
    }
    Knapsack_data *bag[hh+1][k+1];
    for(int i=0;i<=hh;i++)
    {
        for(int j=0;j<=k;j++)
        {
            bag[i][j]=NULL;
        }
    }
    for(int a=1;a<=hh;a++)
    {
        for(int b=1;b<=k;b++)
        {
            pouch[a][b]=pouch[a][b-1];
            Joining_for_Bounded(k,bag,a,b,a,b-1,-1);
            if(load[b-1]<=a)
            {
                int p = pouch[a][b];
                pouch[a][b]=Highest(pouch[a][b],pouch[a-load[b-1]][b-1]+cost[b-1]);
                if(p!=pouch[a][b])
                {
                    Joining_for_Bounded(k,bag,a,b,a-load[b-1],b-1,b);
                }
            }
        }
    }    
    printf("The value of objects in 0/1 knapsack for the given weight is : %d\n",pouch[hh][k]);
    printf("Objects in the Bounded Knapsack are : ");
    Bounded_mark_Knapsack(k,bag,hh,k);
}

void main()
{
    char name[100];
    FILE* file_pr;
    printf("Enter the name of the File : ");
    scanf("%s",name);
    file_pr = fopen(name,"r");
    int size;
    fscanf(file_pr,"%d",&size);
    int load[size],cost[size],hh;
    for(int j=0;j<size;j++)
    {
        fscanf(file_pr,"%d",&load[j]);
        fscanf(file_pr,"%d",&cost[j]);
    }
    fclose(file_pr);
    printf("\nEnter the size of Unbounded knapsack : ");
    scanf("%d",&hh);
    printf("\n------------------------------\n");
    printf("Performing Unbounded Knapsack");
    printf("\n------------------------------\n\n");
    Knapsack_for_Unbounded(size,hh,load,cost);
    printf("\nEnter the size of 0/1 knapsack : ");
    scanf("%d",&hh);
    printf("\n-----------------------------\n");
    printf("Performing Bounded Knapsack");
    printf("\n-----------------------------\n\n");
    KnapSack_for_Bounded(size,hh,load,cost);
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
}