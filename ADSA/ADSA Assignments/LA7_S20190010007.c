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
    int stime;
    int ftime;
    struct node *next;

}DFSGraph;

DFSGraph *new(int x)
{
    DFSGraph *t = (DFSGraph*)malloc(sizeof(DFSGraph));
    t->key=x;
    t->stime=0;
    t->ftime=0;
    t->next=NULL;
    return t;
}

void Insertion(DFSGraph *Graph[],int l,int p,int q)
{
    if(p > l)
    {
        printf("\n--------------------------------------\n");
        printf("Given vertex is not present in the graph\n");
        printf("\n--------------------------------------\n");
        return;
    }
    DFSGraph *bef=Graph[p];
    DFSGraph *pre=Graph[p]->next;
    while(pre!=NULL)
    {
        bef=pre;
        pre=pre->next;
    }
    bef->next=new(q);
}

int DFSTraversal(DFSGraph *G[],int stayed[],int x,int preT)
{
    G[x]->stime=preT;
    preT++;
    stayed[x]=2; 
    DFSGraph *pre=G[x]->next;
    while(pre!=NULL)
    {
        if(stayed[pre->key]==0) 
        {
            preT=DFSTraversal(G,stayed,pre->key,preT);
        }
        preT++;
        pre=pre->next;
    }
    G[x]->ftime=preT;
    stayed[x]=1; 
    printf("%d ",x);
    return preT;
}

int top=-1;

int isEmpty()
{
    if(top==-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }    
}

void push(DFSGraph *stack[],int s,DFSGraph *x)
{
    if(top>=s)
    {
        printf("\n--------------------------------\n");
        printf("Overflow Condition : Stack is Full\n");
        printf("\n--------------------------------\n");
    }
    else
    {
        top+=1;
        stack[top]=x;
    }
}

void pop(DFSGraph *stack[],int s)
{
    if(!isEmpty())
    {
        printf("%d ",stack[top]->key);
        top-=1;   
    }
    else
    {
        printf("\n----------------------------------\n");
        printf("Underflow condition : Stack is Empty\n");
        printf("\n----------------------------------\n");
    }
}

void iterative_DFS(DFSGraph *G[],int stayed[],int start,int l)
{
    //int stayed[l],start;
    for(int i=0;i<l;i++)
    {
        stayed[i]=0;
    }
    int t = DFSTraversal(G,stayed,start,0);
    for(int i=0;i<l;i++)
    {
        if(stayed[i]==0)
        {
            t=DFSTraversal(G,stayed,i,t);
        }
    }
    //printf("\nCost for Iterative DFS is : %d\n",t);
}

int main()
{
    int l;
    printf("Enter the no.of nodes in the Graph : ");
    scanf("%d",&l);
    DFSGraph *G[l];
    for(int i=0;i<l;i++)
    {
        G[i]=new(i);
    }
    int counter=1,p,q,dir;
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
            Insertion(G,l,p,q);
            if(!dir)
            {
                Insertion(G,l,q,p);
            }
        }
        else if(counter==0)
        {
            printf("Exiting.... Performing next task \n");   
        }
        else
        {
            printf("\n-----------\n");
            printf("Invalid Input\n");
            printf("\n-----------\n");
        }
    }
    int stayed[l],start;
    for(int i=0;i<l;i++)
    {
        stayed[i]=0;
    }
    printf("\n----------------\n");
    printf("Performing DFS");
    printf("\n----------------\n");
    printf("Enter a vertex to start DFS from that partocular vertex : ");
    scanf("%d",&start);
    while(start>=l)
    {
        printf("Entered vertex is out of range\n");
        printf("Enter a vertex to start DFS from that partcular vertex : ");
        scanf("%d",&start);
    }
    printf("\nRecursive DFS Traversal from %d is : ",start);
    int t = DFSTraversal(G,stayed,start,0);
    for(int i=0;i<l;i++)
    {
        if(stayed[i]==0)
        {
            t=DFSTraversal(G,stayed,i,t);
        }
    }
    //printf("\nTime elapsed = %.10lf seconds\n", (double)(e1 - s1) / CLOCKS_PER_SEC);

    printf("\nIterative DFS traversal from %d is : ",start);
    clock_t s1 = clock();
    iterative_DFS(G,stayed,start,l);
    clock_t e1 = clock();
    printf("\n----------------------\n");
    printf("Cost for DFS is : %d",t);
    printf("\n----------------------\n");
    printf("\nTime elapsed = %.10lf seconds\n", (double)(e1 - s1) / CLOCKS_PER_SEC);

    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
}