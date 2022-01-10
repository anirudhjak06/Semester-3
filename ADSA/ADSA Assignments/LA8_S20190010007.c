//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct node
{
    int key;
    int level;
    struct node *next;
}BFSGraph;

BFSGraph *CreateNode(int key)
{
    BFSGraph *t = (BFSGraph*) malloc(sizeof(BFSGraph));
    t->key=key;
    t->level=0;
    t->next=NULL;
    return t;
}
void Insertion(BFSGraph *Graph[],int l,int p,int q)
{
    if(p > l)
    {
        printf("\n--------------------------------------\n");
        printf("Given vertex is not present in the graph\n");
        printf("\n--------------------------------------\n");
        return;
    }
    BFSGraph *bef=Graph[p];
    BFSGraph *pre=Graph[p]->next;
    while(pre!=NULL)
    {
        bef=pre;
        pre=pre->next;
    }
    bef->next=CreateNode(q);
}

typedef struct q
{
    int key;
    struct q *next;
}Q;

Q *f=NULL;
Q *r=NULL;

Q *Create(int x)
{
    Q *t = (Q*)malloc(sizeof(Q));
    t->key=x;
    t->next=NULL;
    return t;
}

void Inserting(int x)
{
    Q *t = Create(x);
    if(f==NULL)
    {
        f=t;
        r=t;
    }
    else
    {
        r->next=t;
        r=t;
    }
}

Q *Deleting()
{
    if(f==NULL)
    {
        return NULL;
    }
    else if(f==r)
    {
        Q *t=f;
        f=NULL;
        r=NULL;
        return t;
    }
    else
    {
        Q *t = f;
        f=t->next;
        t->next=NULL;
        return t;   
    }
}

void BFS_AdjM(int n,int m[][n],int stayed[],int p)
{
    Inserting(p);
    stayed[p]=1;
    while(f!=NULL)
    {
        int k= Deleting()->key;
        printf("%d ",k);
        for(int i=0;i<n;i++)
        {
            if(m[k][i]==1 && stayed[i]==0)
            {
                Inserting(i);
                stayed[i]=1; 
            }
        }
    }    
}

void BFS_AdjRecord(BFSGraph *record[],int stayed[],int k)
{
    Inserting(k);
    stayed[k]=1;
    int i=0;
    record[k]->level=i;
    while(f!=NULL)
    {
        Q *p = Deleting();
        printf("%d ",p->key);
        BFSGraph *pre = record[p->key]->next;
        while(pre!=NULL)
        {
            if(stayed[pre->key]==0)
            {
                Inserting(pre->key);
                stayed[pre->key]=1;
                record[pre->key]->level=i+1;
            }
            pre=pre->next;
        }
        i++;
    }
}

int IsBipartite(int n,BFSGraph *record[],int k)
{
    int shade[n];
    for(int i=0;i<n;i++)
    {
        shade[i]=-1;
    }
    shade[k]=1;
    Inserting(k);
    while(f!=NULL)
    {
        int p = Deleting()->key;
        BFSGraph *pre = record[p]->next;
        while(pre!=NULL)
        {
            if(pre->key==p)
            {
                return 0;
            }
            if(shade[pre->key]==-1)
            {
                shade[pre->key]=1-shade[p];
                Inserting(pre->key);
            }
            else if(shade[pre->key]==shade[p])
            {
                return 0;
            }
            pre=pre->next;
        }    
    }
    return 1;
}

int main()
{
    int l;
    printf("Enter the no.of nodes in the Graph: ");
    scanf("%d",&l);
    BFSGraph *record[l];
    int m[l][l];
    for(int i=0;i<l;i++)
    {
        record[i]=CreateNode(i);
    }
    for(int i=0;i<l;i++)
    {
        for(int j=0;j<l;j++)
        {
            m[i][j]=0;
        }
    }
    int dir;
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
    int counter=1,p,q;
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
            m[p][q]=1;
            if(!dir)
            {
                Insertion(record,l,q,p);
                m[q][p]=1;
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
    int stayed[l];
    for(int i=0;i<l;i++)
    {
        stayed[i]=0;
    }
    int k;
    printf("\n----------------\n");
    printf("Performing BFS");
    printf("\n----------------\n");
    printf("Enter a vertex to start BFS from that particular vertex : ");
    scanf("%d",&k);
    printf("\n(i) BFS using ajacency matrix : ");
    BFS_AdjM(l,m,stayed,k);
    printf("\n");
    for(int i=0;i<l;i++)
    {
        stayed[i]=0;
    }
    printf("\n(ii) BFS using adjacency list : ");
    BFS_AdjRecord(record,stayed,k);
    printf("\n");
    printf("\nPrinting Key and level : ");
    for(int i=0;i<l;i++)
    {
        printf("%d->%d  ",record[i]->key,record[i]->level);
    }
    printf("\n");
    //Testing Bipartiteness
    if(IsBipartite(l,record,k))
    {
        printf("\n----------------------------------\n");
        printf("(iii) The given graph is Bipartite Graph");
        printf("\n----------------------------------\n");
    }
    else
    {
        printf("\n----------------------------------------\n");
        printf("(iii) The given graph is not a Bipartite Graph");
        printf("\n----------------------------------------\n");    
    }
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
}