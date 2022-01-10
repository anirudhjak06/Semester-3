//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct up_tree
{
    int categorize;
    int guardian;
}Up_treedata;

typedef struct side
{
    int start;
    int end;
}Side_Data;

typedef struct graph
{
    int lead;
    struct graph *after;
}Graph_data;


Graph_data *CreateNode(int x)
{
    Graph_data *obj = (Graph_data*)malloc(sizeof(Graph_data));
    obj->lead=x;
    obj->after=NULL;
    return obj;
}

void Pushing(Graph_data *record[],int l,int p,int q)
{
    if(p > l)
    {
        printf("\n--------------------------------------\n");
        printf("Given vertex is not present in the graph\n");
        printf("\n--------------------------------------\n");
        return;
    }
    Graph_data *bef=record[p];
    if(bef==NULL)
    {
        record[p]=CreateNode(q);
        return;
    }
    Graph_data *pre=record[p]->after;
    while(pre!=NULL)
    {
        bef=pre;
        pre=pre->after;
    }
    bef->after=CreateNode(q);
}

int Discover_data(Up_treedata batch[],int index)
{
    if(batch[index].guardian!=index)
    {
        batch[index].guardian = Discover_data(batch,batch[index].guardian);
    }
    return batch[index].guardian;    
}

void Joining(Up_treedata batch[],int p,int q)
{
    int x_pos=Discover_data(batch,p);
    int y_pos=Discover_data(batch,q);
    if(batch[x_pos].categorize < batch[y_pos].categorize)
    {
        batch[x_pos].guardian=y_pos;
    }
    else if(batch[x_pos].categorize > batch[y_pos].categorize)
    {
        batch[y_pos].guardian=x_pos;
    }
    else
    {
        batch[y_pos].guardian=x_pos;
        batch[x_pos].categorize++;   
    }
}

Side_Data Chance(Side_Data list[],int stayed[],int border)
{
    int j = rand()%border;
    while(stayed[j]==1)
        j = rand()%border;
    stayed[j]=1;
    return list[j];
}

int Random_Karger_Algo(int size,Graph_data *record[],int border)
{
    int compute=0,stayed[border];
    Side_Data *list = (Side_Data*) malloc(border * sizeof(Side_Data));
    Up_treedata *batch = (Up_treedata*) malloc(size * sizeof(Up_treedata));
    for(int j=0;j<size;j++)
    {
        batch[j].guardian=j;
        batch[j].categorize=0;
        Graph_data *instant = record[j];
        if(instant==NULL)
        {
            continue;
        } 
        while(instant!=NULL)
        {
            stayed[compute]=0;
            list[compute].start=j;
            list[compute].end=instant->lead;
            compute++;
            instant=instant->after;
        }
    }
    int apex = size,side=0;
    while(apex>2)
    {
        Side_Data k = Chance(list,stayed,border);
        int start = Discover_data(batch,k.start);
        int end = Discover_data(batch,k.end);
        if(start==end)
        {
            continue;
        }
        apex--;
        Joining(batch,start,end);    
    } 
    for(int j=0;j<border;j++)
    {
        int start = Discover_data(batch,list[j].start);
        int end = Discover_data(batch,list[j].end);
        if(start!=end)
        {
            side++;
        }
    }
    return side;
}

void main()
{
    int l;
    printf("Enter the no.of nodes in the Graph : ");
    scanf("%d",&l);
    Graph_data *record[l];
    for(int j=0;j<l;j++)
    {
        record[j]=NULL;
    }
    printf("The Graph contains the vertices : ");
    for(int j=0;j<l;j++)
    {
        printf("%d ",j);
    }
    int counter=1,p,q,border=0;
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
            Pushing(record,l,p,q);
            border++;
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
    srand(time(NULL));
    int least = -1;
    int error = (l*(l-1))/2 * (log(1/0.001));
    float likeliness = (float)(2 /(float)(l*(l-1)));
    float compute;
    printf("\n-------------------\n");
    printf("NOTE : Delta = 0.001");
    printf("\n-------------------\n");
    printf("Probability of success is : %f",likeliness);
    printf("\nNo. of Trials : %d",error);
    for(int j=0;j<error;j++)
    {
        int ans = Random_Karger_Algo(l,record,border);
        if(least==-1)
        {
            least = ans;
        }
        else if(least>ans)
        {
            least = ans;  
        }  
    }
    printf("\nMin Cut found by Karger's randomized Algorithm is : %d",least);
    for(int k=0;k<10000;k++)
    {
        int ans = Random_Karger_Algo(l,record,border);
        if(ans==least)
        {
            compute+=1;
        }
    }
    float price = compute/10000;
    printf("\nRunning the algorithm 10,0000 times .....\n");
    printf("\nNOTE : Success is always between 0 to 1\n");
    printf("\nThe Rate of Success is : %f",price);
    int ans = Random_Karger_Algo(l,record,border);
    printf("\nThe diff comparing with the first one is : %f\n",likeliness-price);
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
}