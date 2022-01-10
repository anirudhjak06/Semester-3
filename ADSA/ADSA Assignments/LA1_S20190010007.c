#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void insertion_sort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        int key=a[i];
        int j=i-1;
        while(j>=0 && a[j]>key)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
}

void merge(int a[],int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int L[n1],R[n2];
    int i,j,k;
    for(i=0;i<n1;i++)
    {
        L[i]=a[p+i];
    }
    for(j=0;j<n2;j++)
    {
        R[j]=a[q+1+j];
    }
    i=0;j=0;k=p;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
        {
            a[k]=L[i];
            i++;
        }
        else
        {
            a[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        a[k]=L[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        a[k]=R[j];
        j++;
        k++;
    }       
}

void merge_sort(int a[],int p,int r)
{
    if (p<r)
    {
        int q=(p+r)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    }
}

void swap(int *s1,int *s2)
{
    int temp=*s1;
    *s1=*s2;
    *s2=temp;
}

int partition(int a[],int l,int h)
{
    int pi=a[h];
    int i=(l-1);
    for(int j=l;j<=h-1;j++)
    {
        if(a[j]<pi)
        {
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[h]);
    return (i+1);
}

void quick_sort(int a[],int l,int h)
{
    if(l<h)
    {
        int j=partition(a,l,h);

        quick_sort(a,l,j-1);
        quick_sort(a,j+1,h);
    }
}

void heapify(int a[], int n, int i)
{   
    int left = 2*i + 1, right = 2*i + 2, last = i;  
    if (left < n && a[left] > a[last])
        last = left;
  
    if (right < n && a[right] > a[last])
        last = right;
  
    if (last != i)
    {    
        swap(&a[i], &a[last]);
        heapify(a, n, last);
    }
}

void heap_sort(int a[],int n)
{
    for(int i=n/2-1;i>=0;i--)
    {
        heapify(a,n,i);
    }
    for(int i=n-1;i>0;i--)
    {
        swap(&a[0],&a[i]);
        heapify(a,i,0);
    }
}

void print(int a[],int n)
{
    printf("\nThe elements after sorting : ");
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n\n");
}

int main()
{
    while(1)
	{
		printf("Please select appropiate no. for your task\n");
		printf("1- To Quit\n");
        printf("2- To perform Insertion Sort\n");
        printf("3- To perform Merge Sort\n");
        printf("4- To perform Quick Sort\n");
        printf("5- To perform Heap Sort\n");
        int ch;
		scanf("%d",&ch);
		if(ch==1) 
        {
            break;
        }
        int n;
        printf("Enter the size of the array : ");
        scanf("%d", &n);
        int a[n];
        for (int i=0;i<n;i++)
        {
            printf("Enter the %d element :", i+1);
            scanf("%d", &a[i]);
        }
        printf("\nThe elements before sorting : ");
        for (int i=0;i<n;i++)
            printf("%d ", a[i]);

	    switch(ch)
	    {
            case 2: 
                    insertion_sort(a,n);
                    print(a,n);
                    break;
            case 3: 
                    merge_sort(a,0,n-1);
                    print(a,n);
                    break;
            case 4: 
                    quick_sort(a,0,n-1);
                    print(a,n);
                    break;
            case 5 : 
                    heap_sort(a,n);
                    print(a,n);
                    break;                                
            default :printf("You have entered an invalid number\n");
        }
    }
    printf("Thank You! I hope you have got the required details\n");
}