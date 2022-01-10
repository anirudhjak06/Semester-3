//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct graph
{
    int lead;
    int load;
    struct graph *after;
}Graph_data;

Graph_data *CreateNode(int p, int weight)
{
    Graph_data *obj = (Graph_data*)malloc(sizeof(Graph_data));
    obj->lead=p;
    obj->load=weight;
    obj->after=NULL;
    return obj;
}


void Insertion(Graph_data *record[],int l,int p,int q,int weight)
{
    if(p > l)
    {
        printf("\n--------------------------------------\n");
        printf("Given vertex is not present in the graph\n");
        printf("\n--------------------------------------\n");
        return;
    }
    Graph_data *bef=record[p];
    Graph_data *pre=record[p]->after;
    while(pre!=NULL)
    {
        bef=pre;
        pre=pre->after;
    }
    bef->after=CreateNode(q,weight);
}

int Min(int p,int q,int r)
{
    if(p<=q && p<=r)
    {
        return p;
    }
    if(q<=r && q<=p)
    {
        return q;
    }
    if(r<=p && r<=q)
    {
        return r;
    }        
}

void Bell_Ford_Algo(Graph_data *record[],int l,int k)
{
    int len[l][l];
    for(int j=0;j<l;j++)
    {
        len[0][j]=10000;
    }
    len[0][k]=0;
    for(int i=0;i<l-1;i++)
    {
        for(int m=0;m<l;m++)
        {
            len[i+1][m]=len[i][m];
        }
        for(int p=0;p<l;p++)
        {
            Graph_data *pre = record[p]->after;
            while(pre!=NULL)
            {
                len[i+1][pre->lead] = Min(len[i][pre->lead],len[i+1][pre->lead],len[i][p]+pre->load);
                pre=pre->after;    
            }
        }
    }
    for(int m=0;m<l;m++)
    {
        if(len[l-1][m]!=len[l-2][m])
        {
            printf("\n------------------------------\n");
            printf("The Given graph contains Neg cycle");
            printf("\n------------------------------\n");
            return;
        }
    }
    printf("\nNo Neg cycle is present in graph\n\n");
    for(int j=0;j<l;j++)
    {
        if(j==k)
        {
            continue;
        }
        printf("Shortest distance from %d to %d is %d\n",k,j,len[l-1][j]);
    }
}

void main()
{
    int l;
    printf("Enter the no.of nodes in the Graph : ");
    scanf("%d",&l);
    Graph_data *record[l];
    for(int i=0;i<l;i++)
    {
        record[i]=CreateNode(i,0);
    }
    printf("The vertices of the Graph are: ");
    for(int j=0;j<l;j++)
    {
        printf("%d ",j);
    }
    int counter=1,p,q,weight;
    while(counter)
    {
        printf("\n-----------\n");
        printf("0 : EXIT\n1 : INSERTION");
        printf("\n-----------\n"); 
        printf("Enter your choice : ");
        scanf("%d",&counter);
        if(counter==1)
        {
            printf("Enter a pair of edge : ");
            //printf("Enter the edge between 0 to %d",l);
            scanf("%d %d",&p,&q);
            printf("Enter the weight of the edge : ");
            scanf("%d",&weight);
            //total+=1;
            Insertion(record,l,p,q,weight);
        }
        else if(counter==0)
        {
            printf("Exiting.... Performing next task\n");   
        }
        else
        {
            printf("\n-----------\n");
            printf("Invalid Input\n");
            printf("\n-----------\n");
        }
    }
    //printf("\n--------------------------\n");
    printf("\nPerforming Bellman Ford algorithm ");
    //printf("\n--------------------------\n");
    printf("\nEnter a vertex to start : ");
    scanf("%d",&weight);
    printf("\n----------------------------------------------------------------------\n");
    printf("NOTE :\n(i) Here 10,000 is taken instead of infinity");
    printf("\n(ii) 10,000 is printed if there is no edge or path between %d and any other edge",weight);
    // printf("\n(iii) The representation is from right to left ");
    // printf("\n(iv) The number in parenthesis denote the edge weight");
    printf("\n----------------------------------------------------------------------\n");
   
    Bell_Ford_Algo(record,l,weight);
    
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
}