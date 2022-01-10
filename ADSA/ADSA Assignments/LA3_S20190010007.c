#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int Maximum(int a[],int n)
{
    int m=a[0];
    for(int i=1;i<n;i++)
    {
        if(a[i]>m)
        {
            m=a[i];
        }
    }
    return m;
}

void CountSort(int a[],int n,int pos,int base)
{
    int b[n],i,count[base];
    for(i=0;i<base;i++)
    {
        count[i]=0;
    }
    for(i=0;i<n;i++)
    {
        count[(a[i]/pos)%base]++;
    }
    for(i=1;i<base;i++)
    {
        count[i]+=count[i-1];
    }
    for(i=n-1;i>=0;i--)
    {
        b[count[(a[i]/pos)%base]-1]=a[i];
        count[(a[i]/pos)%base]--;
    }
    for(i=0;i<n;i++)
    {
        a[i]=b[i];
    }
}

void RadixSort(int a[],int n,int base)
{
    int max=Maximum(a,n);
    for(int pos=1;max/pos>0;pos=pos*base)
    {
        CountSort(a,n,pos,base);
    }
}

void print(int a[],int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}

void analysis(int t[],int n,int base)
{
    clock_t start,stop;
    int temp[n];
    for(int i=0;i<n;i++)
    {
        temp[i]=t[i];
    }
    printf("\nNOTE : Analysis by varying the base from %d to %d i.e. 15 elements is\n\n",(base+1),(base+15));
    for(int i=(base +1);i<=(base+15);i++)
    {
        start = clock();
        RadixSort(t, n,i);
        stop = clock() - start;
        double time_taken = ((double)stop) / CLOCKS_PER_SEC;
        printf("Time taken for Radix Sort of base %d = %f seconds\n",i,time_taken);
        for(int j=0;j<n;j++)
        {
            t[i]=temp[i];
        }
    }
    printf("\n");
}

typedef struct node 
{
    int value;
    struct node *left,*right;
}BSearchT;

BSearchT* CreateNode(int value)
{
    BSearchT *t=(BSearchT*)malloc(sizeof(BSearchT));
    t->value=value;
    t->left=t->right=NULL;
    return t;
}

void InorderTraversal(BSearchT *child) 
{
    if(child!=NULL) 
    {
        InorderTraversal(child->left);
        printf("%d ",child->value);
        InorderTraversal(child->right);
    }
}

BSearchT* Successor(BSearchT* child)
{
    BSearchT* t = child;
    while(t && t->left!=NULL)
    {
        t=t->left;
    }
    return t;
}

BSearchT* Searching(BSearchT *child,int x)
{
    if(child==NULL || child->value == x)
    {
        return child;
    }
    if(child->value > x)
    {
        return Searching(child->left,x);
    }
    else
    {
        return Searching(child->right,x);
    }
    return NULL;
}

BSearchT* Insertion(BSearchT *child,int key) 
{
    if(child == NULL)
    {
        return CreateNode(key);
    }
    if(child->value>key)
    {
        child->left = Insertion(child->left,key);
    }
    else
    {
        child->right = Insertion(child->right,key);
    }
    return child;
}

BSearchT* Deletion(BSearchT *child,int val) 
{
    if(child==NULL)
    {
        return child;
    }
    if(val>child->value)
    {
        child->right = Deletion(child->right,val);
    }
    else if(val<child->value)
    {
        child->left = Deletion(child->left,val);
    }
    else 
    {
        if(child->right==NULL) 
        {
            BSearchT *t = child->left;
            free(child);
            return t;
        }
        else if(child->left==NULL) 
        {
            BSearchT *t = child->right;
            free(child);
            return t;
        }
        BSearchT *t =  Successor(child->right);
        child->value = t->value;
        child->right=Deletion(child->right,t->value);
    }
    return child;
}

int main()
{
    clock_t t1_s,t1_e;
    while(1)
	{
		printf("Please select appropiate no. for your task\n");
        printf("NOTE : For Analysing Radix Sort,uncomment analysis function\n");
		printf("1- To Quit\n");
        printf("2- To perform Radix Sort\n");
        printf("3- To perform Insertion,Deletion and Searching in BST\n");
        int ch;
		scanf("%d",&ch);
		if(ch==1) 
        {
            break;
        }
        else if (ch>=4)
        {
            printf("Invalid Input\n");
            break;
        }
        int n,base;
        printf("Enter the size of the array : ");
        scanf("%d", &n);
        int a[n],t[n];
        printf("Enter the array elements : ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++)
        {
            t[i]=a[i];
        }
        switch (ch)
        {
            case 2: 
            {
                printf("The elements before sorting : ");
                print(a,n);
                printf("Enter the base value for Radix Sort : ");
                scanf("%d", &base);
                t1_s = clock();
                RadixSort(a, n, base);
                t1_e = clock() - t1_s;
                double time_taken1 = ((double)t1_e) / CLOCKS_PER_SEC;
                printf("Time taken = %f seconds\n", time_taken1);
                printf("\nThe elements after Radix Sort : ");
                print(a, n);
                //analysis(t,n,base);
                break;
            }
            case 3: 
            {
                BSearchT *root=NULL;
                for(int i=0;i<n;i++)
                {
                    root=Insertion(root,a[i]);
                }
                printf("The Inserted elements in tree are : ");
                print(a,n);
                printf("\nInorder Traversal of the tree : ");
                InorderTraversal(root);
                printf("\n");
                int se;
                printf("\nEnter element to search in the tree: ");
                scanf("%d",&se);
                if(Searching(root,se)==NULL)
                {
                    printf("There is no element %d in the tree\n",se);
                }
                else
                {
                    printf("Found the element : %d\n",se);
                }
                int ie;
                printf("\nEnter element to insert in the tree: ");
                scanf("%d",&ie);
                root=Insertion(root,ie);
                printf("\nElements after inserting %d : ",ie);
                InorderTraversal(root);
                int de;
                printf("\nEnter the element to Delete : ");
                scanf("%d",&de);
                root=Deletion(root,de);
                printf("\nElements after deleting %d : ",de);
                InorderTraversal(root);
                printf("\n\n");
                break;
            }
            default:
                printf("You have entered an invalid number\n");
        }
    }
    printf("\nThank You! I hope you have got the required details\n");
}