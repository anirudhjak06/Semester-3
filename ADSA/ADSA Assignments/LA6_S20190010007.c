#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct hashing
{
    int data;
    struct hashing * next;
}hashing;


void Insertion(hashing *arr[], int data, int pos)
{
    hashing *new = (hashing *)malloc(sizeof(hashing)); 
    new->data = data;
    new->next = NULL;
    if (arr[pos] == NULL) 
    {
        arr[pos] = new;
    }
    else
    {
        new->next=arr[pos];
        arr[pos]=new;
    }
}

int NHashf(int b,int y)
{
    return b%y;
}

void Searching(hashing* arr[],int value,int l)
{
    printf("Searching for key %d : \n",value);
    int pos = NHashf(value,l),f = 0;
    hashing *t;
    t = arr[pos];
    while(t!=NULL)
    {
        if(t->data = value)
        {
            printf("%d : is present\n",value);
            f = 1;
            break;
        }
        t=t->next;
    }
    if(f == 0)
    {
        printf("The element is not present\n");
    }
}

void HashingFunc(int *arr, int n)
{
    int l = 10;
    hashing *b[l];   
    for(int i=0;i<l;i++)
    {
        b[i]=NULL;
    }
    for(int i=0;i<n;i++)
    {
        int pos = NHashf(arr[i],l);
        Insertion(b,arr[i],pos); 
    }
    printf("\nPrinting the Hash Table : \n");
    for(int i=0;i<l;i++)
    {
        hashing *t = b[i];
        printf("%d ",i);
        while(t!=NULL)
        {
            printf("%d -> ",t->data);
            t = t->next;
        }
        printf("NULL\n");
    }
    double total = 0.0;
    srand(time(NULL));
    for(int i=0;i<100;i++)
    {
        int key;
        if(i%5==0)
        {
            key = (rand()%10000);
        }
        else
        {
            int index = (rand()%n);
            key = arr[index];
        }   
        clock_t start1 = clock(); 
        /*printf("\n-------------------------\n");
        printf("Performing SEARCH Operation\n");
        printf("\n-------------------------\n");*/
        Searching(b,key,l);
        clock_t end1 =clock();
        total+=(double)(end1-start1)/CLOCKS_PER_SEC;
    }
    printf("\n------------------------------------------------------------\n");
    printf("The Avg time taken for Searching is : %.10lf seconds\n",total/100);
    printf("\n------------------------------------------------------------\n");    
}

int Uhashfunc1(int x)
{
    return x%17;
}

int Uhashfunc2(int x)
{
    return x%23;
}

void SearchingU(hashing* b[],int key,int x)
{
    printf("Searching for key : %d\n",key);
    int pos=(Uhashfunc1(key)^Uhashfunc2(key))%x,f=0;
    hashing *temp=b[pos];
    while(temp!=NULL)
    {
        if(temp->data == key)
        {
            f=1;
            printf("The element is present :\n");
            break;
        }
        temp=temp->next;
    }
    if(f==0)
    {
       printf("The element is not present\n");
    }
}

void UhashingFunc(int *arr,int n)
{
    int size=41;
    hashing *b[size];
    for(int i=0;i<size;i++)
    {
        b[i]=NULL;
    }
    for(int i=0;i<n;i++)
    {
        int pos = (Uhashfunc1(arr[i])^Uhashfunc2(arr[i]))%size;
        Insertion(b,arr[i],pos); 
    }
    printf("\nPrinting the Hash Table : \n");
    for(int i=0;i<size;i++)
    {
        hashing *t = b[i];
        printf("%d ",i);
        while(t!=NULL)
        {
            printf("%d -> ",t->data);
            t = t->next;
        }
        printf("NULL\n");
    }
    double total = 0.0;
    srand(time(NULL));
    for(int i=0;i<100;i++)
    {
        int key;
        if(i%5==0)
        {
            key = (rand()%10000);
        }
        else
        {
            int index = (rand()%n);
            key = arr[index];
        }
        clock_t start2 = clock(); 
        // printf("\n-------------------------\n");
        // printf("Performing SEARCH Operation\n");
        // printf("\n-------------------------\n");
        SearchingU(b,key,size);
        clock_t end2 =clock();
        total+=(double)(end2-start2)/CLOCKS_PER_SEC;
    }
    printf("\n---------------------------------------------------------\n");
    printf("The Avg time taken for Searching : %.10lf seconds\n",total/100);
    printf("\n---------------------------------------------------------\n");
}

int main()
{
    srand(time(NULL));
    /*Normal hash Function*/
    printf("\n-----------------------------------\n");
    printf("Normal Hash Function : H(x) : x %% 10\n");
    printf("\n-----------------------------------\n");
    printf("Enter the no.of elements: ");
    int n;
    scanf("%d",&n);
    int a[n];
    printf("Randomly generating array elements.....\n");
    printf("Printing the array elements : ");
    for(int i=0;i<n;i++)
    {
        a[i]=1+rand()%1000000;
        printf("%d ",a[i]);
    }
    printf("\n");
    HashingFunc(a,n);
    // Universal Hash function
    printf("\n----------------------------------------------------\n");
    printf("Universal Hash Function : H(x) : (h1(x)^h2(x)) %% 41 :\n"); 
    printf("where, h1(x) : x %% 17 and h2(x) : x %% 23\n");
    printf("\n----------------------------------------------------\n");
    printf("Enter the no.of elements: ");
    int n1;
    scanf("%d",&n1);
    int arr[n1];
    printf("Randomly generating array elements.....\n");
    printf("Printing the array elements : ");
    for(int i=0;i<n1;i++)
    {
        arr[i]=1+rand()%1000000;
        printf("%d ",arr[i]);
    }
    printf("\n");
    UhashingFunc(arr,n1);
}