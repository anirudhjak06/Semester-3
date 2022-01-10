#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<math.h>

void swap(int *s1, int *s2)
{
    int temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void shuffling(int a[], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        swap(&a[i], &a[rand() % n]);
    }
}

bool sorted(int a[], int n)
{
    while (--n >= 1)
    {
        if (a[n] < a[n - 1])
        {
            return false;
        }
    }
    return true;
}

void Bogo_sort(int a[], int n)
{
    while (!sorted(a, n))
    {
        shuffling(a, n);
    }
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int partition(int a[], int l, int h)
{
    int p_i = l + rand()%(h-l+1);
    int i = l - 1;
    int pivot=a[p_i];
    swap(&a[p_i],&a[h]);
    for (int j = l; j < h; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[h]);
    return i + 1;
}

void quick_sort(int a[], int l, int h)
{
    if (l < h)
    {
        int j = partition(a, l, h);

        quick_sort(a, l, j - 1);
        quick_sort(a, j + 1, h);
    }
}

float calculateMean(float data[], int n)
{
    float sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < n; ++i)
    {
        sum += data[i];
    }
    mean = sum / n;
    return mean;
}

float calculateSD(float data[], int n)
{
    float sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < n; ++i)
    {
        sum += data[i];
    }
    mean = sum / n;
    for (i = 0; i < n; ++i)
        SD += pow(data[i] - mean, 2);
    return (sqrt(SD / n));
}

void print2(double time_taken,int k,float t[])
{
    printf("\nMean = %.6f\n", calculateMean(t, k));
    printf("\nStandard Deviation = %.6f\n\n", calculateSD(t, k));
}

int main()
{
    clock_t t1_s,t2_s,t3_s,t1_e,t2_e,t3_e;
    int k1=0,k2=0,k3=0,m=1;
    float t1[100]={0},t2[100]={0},t3[100]={0}; 
    while (1)
    {
        printf("Please select appropiate no. for your task\n");
        printf("NOTE : For Analysing STD and MEAN,uncomment print2 function\n");
        printf("1- To Quit\n");
        printf("2- To perform Bogo Sort\n");
        printf("3- To perform Random Quick Sort\n");
        printf("4- To perform Both Bogo and Random Quick Sort\n");
        int ch;
        scanf("%d", &ch);
        if (ch == 1)
        {
            break;
        }
        else if (ch>=5)
        {
            printf("Invalid Input\n");
            break;
        }
        int n;
        printf("Enter the size of the array : ");
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++)
        {
            printf("Enter the %d element :", i + 1);
            scanf("%d", &a[i]);
        }
        printf("\nThe elements before sorting : ");
        print(a, n);
        switch (ch)
        {
            case 2:
                    t1_s=clock();
                    Bogo_sort(a, n);
                    printf("\nThe elements after Bogo sort : ");
                    print(a, n);
                    t1_e = clock() - t1_s; 
                    double time_taken1 = ((double)t1_e)/CLOCKS_PER_SEC;
                    t1[k1]=time_taken1;
                    k1++;
                    printf("Time taken = %f seconds\n",time_taken1);
                    //print2(time_taken1,k1,t1);
                    break;
            case 3:
                    t2_s=clock();
                    shuffling(a,n);
                    quick_sort(a, 0, n - 1);
                    printf("\nThe elements after Quick sort : ");
                    print(a, n);
                    t2_e = clock() - t2_s; 
                    double time_taken2 = ((double)t2_e)/CLOCKS_PER_SEC;
                    t2[k2]=time_taken2;
                    k2++;
                    printf("Time taken = %f seconds\n",time_taken2);
                    //print2(time_taken2,k2,t2);
                    break;
            case 4:
                    t3_s=clock();
                    Bogo_sort(a, n);
                    printf("\nThe elements after Bogo sort : ");
                    print(a, n);
                    shuffling(a,n);
                    quick_sort(a, 0, n - 1);
                    printf("\nThe elements after Quick sort : ");
                    print(a, n);
                    t3_e = clock() - t3_s; 
                    double time_taken3 = ((double)t3_e)/CLOCKS_PER_SEC;
                    t3[k3]=time_taken3;
                    k3++;
                    printf("Time taken = %f seconds\n",time_taken3);
                    //print2(time_taken3,k3,t3);
                    break;
            default:
                    printf("You have entered an invalid number\n");
        }
    }
    printf("\nThank You! I hope you have got the required details\n");
}
