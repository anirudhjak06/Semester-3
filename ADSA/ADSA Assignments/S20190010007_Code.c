//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct dfs
{
    int lead;
    struct dfs *after;
}DFS_Graph;

DFS_Graph *Create_Node(int p)
{
    DFS_Graph *obj = (DFS_Graph*)malloc(sizeof(DFS_Graph));
    obj->lead=p;
    obj->after=NULL;
    return obj;
}

void Insertion(DFS_Graph *record[],int l,int p,int q)
{
    if(p > l)
    {
        printf("\n--------------------------------------\n");
        printf("Given vertex is not present in the graph\n");
        printf("\n--------------------------------------\n");
        return;
    }
    DFS_Graph *instant=record[p];
    if(instant==NULL)
    {
        record[p]=Create_Node(q);
        return;
    }
    DFS_Graph *latest=record[p]->after;
    while(latest!=NULL)
    {
        instant=latest;
        latest=latest->after;
    }
    instant->after=Create_Node(q);
}

void DFS_data(DFS_Graph *record[],int stayed[],int compute[],int w)
{
    stayed[w]=2; // in progress
    DFS_Graph *latest=record[w];
    while(latest!=NULL)
    {
        if(stayed[latest->lead]==0) // not visited
        {
            DFS_data(record,stayed,compute,latest->lead);
        }
        compute[w]+=1;
        if(compute[latest->lead]%2 == 1)
        {
            printf("%d is odd neighbour of vertex %d\n",latest->lead,w);
        }
        latest=latest->after;
    }
    stayed[w]=1; // all done
}



int main()
{
    int l;
    
    printf("Enter the no.of nodes in the Graph : ");
    scanf("%d",&l);
    DFS_Graph *record[l];
    for(int i=0;i<l;i++)
    {
        record[i]=NULL;
    }
    //Printing the vertices of a graph
    printf("The vertices of the Graph are : ");
    for(int j=0;j<l;j++)
    {
        printf("%d ",j);
    }
    printf("\n");
    int counter=1,p,q;
    // Taking input from user to insert or exit
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
            scanf("%d",&p);
            scanf("%d",&q);
            Insertion(record,l,p,q);
            Insertion(record,l,q,p);

        }
        else if(counter==0)
        {
            printf("Exiting.... Performing next task : \n");   
        }
        else
        {
            printf("\n-----------\n");
            printf("Invalid Input\n");
            printf("\n-----------\n");
        }
    }
    //Intializing to zero
    int stayed[l],compute[l],weights;
    for(int j=0;j<l;j++)
    {
        compute[j]=0;
        stayed[j]=0;
    }
    printf("\n----------------\n");
    printf("Performing DFS");
    printf("\n----------------\n");
    //Performing DFS
    printf("Enter a vertex to start DFS from that partcular vertex : ");
    scanf("%d",&weights);
    while(weights>=l)
    {
        printf("Entered vertex is out of Range\n");
        printf("Enter the vertex from which DFS start: ");
        scanf("%d",&weights);
    }
    DFS_data(record,stayed,compute,weights);
    //Odd vertices count
    printf("No of odd vertices for a particular vertex is : ");
    printf("\n");
    for(int j=0;j<l;j++)
    {
        printf("%d -> %d\n",j,compute[j]);
    }
}