//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct graph
{
    int key;
    int weight;
    struct graph *next;
}Graph_data;

typedef struct edge
{
    int start;
    int end;
    int weight;
}Edge_data;

typedef struct heap
{
    int space;
    int pos;
    Edge_data *list;
}Heap_data;

typedef struct tree
{
    int categorize;
    int guardian;
}Up_treedata;

Graph_data *CreateNode(int p, int w)
{
    Graph_data *t = (Graph_data*)malloc(sizeof(Graph_data));
    t->key=p;
    t->weight=w;
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

void Swapping(Edge_data *x,Edge_data *y)
{
    Edge_data t = *x;
    *x = *y;
    *y = t;
}

void Heap_Insertion(Heap_data *pile,int start,int end,int weight)
{
    if(pile->pos==pile->space)
    {
        printf("\n-------------------\n");
        printf("OVERFLOW! Cannot Insert");
        printf("\n-------------------\n");
        return;
    }
    int i=pile->pos;
    pile->pos++;
    pile->list[i].start=start;
    pile->list[i].end=end;
    pile->list[i].weight=weight;
    while(i!=0 && pile->list[(i-1)/2].weight > pile->list[i].weight)
    {
        Swapping(&pile->list[i],&pile->list[(i-1)/2]);
        i=(i-1)/2;
    }
}

void Min_Heapify(Heap_data *pile,int index)
{
    int l= 2*index+1;
    int r= 2*index+2;
    int small = index;
    if(l < pile->pos && pile->list[l].weight < pile->list[index].weight)
    {
        small = l;
    }
    if(r < pile->pos && pile->list[r].weight < pile->list[index].weight)
    {
        small = r;
    }
    if(small!=index)
    {
        Swapping(&pile->list[index],&pile->list[small]);
        Min_Heapify(pile,small);
    }        
}

Edge_data Get_Min_Heap(Heap_data *pile)
{
    if(pile->pos==1)
    {
        pile->pos--;
        return pile->list[0];
    }
    Edge_data root = pile->list[0];
    pile->list[0]=pile->list[pile->pos-1];
    pile->pos--;
    Min_Heapify(pile,0); 
    return root;   
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

int Find_data(Up_treedata batch[],int index)
{
    if(batch[index].guardian!=index)
    {
        batch[index].guardian = Find_data(batch,batch[index].guardian);
    }
    return batch[index].guardian;    
}

void Union_data(Up_treedata batch[],int p,int q)
{
    int x_pos=Find_data(batch,p);
    int y_pos=Find_data(batch,q);
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

void Krushkals_MST_data(Graph_data *record[],int l,int compute,int dir)
{
    Heap_data *pile = CreateHeap(compute);
    for(int i=0;i<l;i++)
    {
        Graph_data *pre=record[i]->next;
        while(pre!=NULL)
        {
            Heap_Insertion(pile,i,pre->key,pre->weight);
            pre=pre->next;
        }
    }
    Graph_data *Min_tree[l];
    for(int i=0;i<l;i++)
    {
        Min_tree[i]=CreateNode(i,0);
    }
    Up_treedata *batch = (Up_treedata*)malloc(l * sizeof(Up_treedata));
    for(int i=0;i<l;i++)
    {
        batch[i].guardian=i;
        batch[i].categorize=0;
    }
    int j=0,k=0;
    printf("\nAfter Sorting : ");
    printf("\nPrinting the details : \n");
    printf("\n|---------------|---------------|---------------|\n");
    printf("| Start edge    | End Edge      | Weight        |");
    printf("\n-------------------------------------------------\n");
    while(k < l-1 && j < compute)
    {
        int flag=1;
        Edge_data edges = Get_Min_Heap(pile);
        j++;
        int p = Find_data(batch,edges.start);
        int q = Find_data(batch,edges.end);
        printf("|\t%d\t|\t%d\t|\t%d\t|\n",edges.start,edges.end,edges.weight);
        if(p!=q)
        {
            flag=0;
        }
        if(!flag)
        {
            Union_data(batch,p,q);
            k++;
            Insertion(Min_tree,l,edges.start,edges.end,edges.weight);
            if(!dir)
            {
                Insertion(Min_tree,l,edges.end,edges.start,edges.weight);
            }
        }
    }
    printf("---------------------------------------------------\n");
    printf("\nFollowing are the edges in the constructed MST : \n");
    //printf("\nPrinting the index,key and weight respectively : \n");
    int array[1000];
    for(int i=0;i<1000;i++)
    {
        array[i]=0;
    }
    int loop=0;
    for(int i=0;i<l;i++)
    {
        Graph_data *pre = Min_tree[i]->next;
        while(pre!=NULL)
        {
            printf("%d-->%d = %d  ",i,pre->key,pre->weight);
            array[loop]=pre->weight;
            loop++;
            pre=pre->next;
        }
        printf("\n");   
    } 
    int sum=0;
    for(int i=0;i<1000;i++)
    {
        sum+=array[i];
    }
    if(dir)
    {
        printf("\nCost of Spanning tree is : %d ",sum);
    }
    else
    {
        printf("\nCost of Spanning tree is : %d ",sum/2);
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
    int total=0,dir;
    printf("\n---------------\n");
    printf("0 : UNDIRECTED \n1 : DIRECTED");
    printf("\n---------------\n");
    printf("Enter your choice : ");
    scanf("%d",&dir);
    printf("The vertices of the Graph are : ");
    for(int i=0;i<l;i++)
    {
        printf("%d ",i);
    }
    printf("\n");
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
            scanf("%d",&p);
            scanf("%d",&q);
            printf("Enter the weight of the edge : ");
            scanf("%d",&weight);
            total+=1;
            Insertion(record,l,p,q,weight);
            if(!dir)
            {
                Insertion(record,l,q,p,weight);
                total+=1;
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
    Krushkals_MST_data(record,l,total,dir);
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
    return 0;    
}