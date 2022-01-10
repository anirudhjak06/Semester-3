//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct tree
{
    int categorize;
    int guardian;
}Up_treedata;

typedef struct edge
{
    int start;
    int info;
}Edge_data;

typedef struct heap
{
    int space;
    int pos;
    Edge_data *list;
}Heap_data;


typedef struct graph
{
    int lead;
    int load;
    struct graph *next;
}Graph_data;



Graph_data *CreateNode(int p, int weight)
{
    Graph_data *t = (Graph_data*)malloc(sizeof(Graph_data));
    t->lead=p;
    t->load=weight;
    t->next=NULL;
    return t;
}

Heap_data *CreateHeap(int space)
{
    Heap_data *t = (Heap_data*)malloc(sizeof(Heap_data));
    t->space=space;
    t->pos=0;
    t->list = (Edge_data*)malloc(space*sizeof(Edge_data));
    return t;
}

void Swapping(Edge_data *a,Edge_data *b)
{
    Edge_data t = *a;
    *a = *b;
    *b = t;
}

void Heap_Insertion(Heap_data *pile,int start,int weight)
{
    if(pile->pos==pile->space)
    {
        printf("\n-------------------\n");
        printf("OVERFLOW! Cannot be Inserted");
        printf("\n-------------------\n");
        return;
    }
    int j=pile->pos;
    pile->pos++;
    pile->list[j].start=start;
    pile->list[j].info = weight;
    while(j!=0 && pile->list[(j-1)/2].info > pile->list[j].info)
    {
        Swapping(&pile->list[j],&pile->list[(j-1)/2]);
        j=(j-1)/2;
    }
}

void Minimum_Heap(Heap_data *pile,int index)
{
    int l= 2*index+1;
    int r= 2*index+2;
    int small = index;
    if(l < pile->pos && pile->list[l].info < pile->list[index].info)
    {
        small = l;
    }
    if(r < pile->pos && pile->list[r].info < pile->list[index].info)
    {
        small = r;
    }
    if(small!=index)
    {
        Swapping(&pile->list[index],&pile->list[small]);
        Minimum_Heap(pile,small);
    }       
}

Edge_data Get_Min_Heap(Heap_data *pile)
{
    if(pile->pos==1)
    {
        pile->pos--;
        return pile->list[0];
    }
    Edge_data obj = pile->list[0];
    pile->list[0]=pile->list[pile->pos-1];
    pile->pos--;
    Minimum_Heap(pile,0); 
    return obj;   
}

int Get_pos(Heap_data *pile,int lead)
{
    int loop;
    for(loop=0;loop<pile->pos;loop++)
    {
        if(pile->list[loop].start==lead)
        {
            return loop;
        }
    }
    return -1;
}

void Heap_Updation(Heap_data *pile,int index,int price)
{   
    pile->list[index].info = price;
    while(index!=0 && pile->list[(index-1)/2].info > pile->list[index].info)
    {
        Swapping(&pile->list[index],&pile->list[(index-1)/2]);
        index=(index-1)/2;
    }
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
    Graph_data *pre=record[p]->next;
    while(pre!=NULL)
    {
        bef=pre;
        pre=pre->next;
    }
    bef->next=CreateNode(q,weight);
}

void Estimation_set(Heap_data *pile,int highest,int l)
{
    for(int i=0;i<l;i++)
    {
        Heap_Insertion(pile,i,highest);
    }
}

void Path_Printer(Up_treedata batch[],int i)
{
    if(batch[i].guardian!=i)
    {
        printf("%d<-(%d)- ",i,batch[i].categorize-batch[batch[i].guardian].categorize);
        Path_Printer(batch,batch[i].guardian);
    }
    else
    {
        printf("%d\n",batch[i].guardian);
    }    
}

void Dijkstra_Algo(int l,Graph_data *record[],int weight)
{
    int stayed[l];
    for(int i=0;i<l;i++)
    {
        stayed[i]=0;
    }
    Heap_data *pile = CreateHeap(l);
    Estimation_set(pile,10000,l);
    Up_treedata *batch = (Up_treedata*)malloc(l * sizeof(Up_treedata));
    for(int j=0;j<l;j++)
    {
        batch[j].guardian=j;
        batch[j].categorize=0;
    }
    Heap_Updation(pile,Get_pos(pile,weight),0);
    while(pile->pos!=0)
    {
        Edge_data p = Get_Min_Heap(pile);
        int vertex = p.start;
        batch[vertex].categorize=p.info;
        Graph_data* pre = record[vertex]->next;
        while(pre!=NULL)
        {
            int m = Get_pos(pile,pre->lead);
            if(m!=-1 && pile->list[m].info > p.info+pre->load )
            {
                Heap_Updation(pile,m,(p.info+pre->load));
                batch[pre->lead].guardian=vertex;
            }
            pre=pre->next;
        }
        stayed[vertex]=1;
    }
    printf("\nShortest path from %d to all vertices is : \n",weight);
    for(int i=0;i<l;i++)
    {
        if(i==weight)
        {
            continue;
        }
        printf("\nShortest distance : (%d)  ",batch[i].categorize);
        printf("\nPath : ");    
        Path_Printer(batch,i);  
    }
    printf("\n");
}

int main()
{
    int l;
    printf("Enter the no.of nodes in the Graph : ");
    scanf("%d",&l);
    Graph_data *record[l];
    for(int i=0;i<l;i++)
    {
        record[i]=CreateNode(i,0);
    }
    int dir;
    printf("\n---------------\n");
    printf("0 : UNDIRECTED \n1 : DIRECTED");
    printf("\n---------------\n");
    printf("Enter your choice : ");
    scanf("%d",&dir);
    printf("The vertices of the Graph are : ");
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
            if(!dir)
            {
                Insertion(record,l,q,p,weight);
                //total+=1;
            }
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
    printf("\nPerforming Dijkstra algorithm ");
    //printf("\n--------------------------\n");
    printf("\nEnter a vertex to start : ");
    scanf("%d",&weight);
    printf("\n----------------------------------------------------------------------\n");
    printf("NOTE :\n(i) Here 10,000 is taken instead of infinity");
    printf("\n(ii) 10,000 is printed if there is no edge between %d and any other edge",weight);
    printf("\n(iii) The representation is from right to left ");
    printf("\n(iv) The number in parenthesis denote the edge weight");
    printf("\n----------------------------------------------------------------------\n");
    Dijkstra_Algo(l,record,weight);
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
    return 0; 
}