//This Assignment is done by Anirudh Jakhotia
// Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void Swap(int a[], int x, int y)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

void Sort(int a[], int n)
{
    int minIndex;
    for (int i = 0; i < n; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        Swap(a, i, minIndex);
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

void problem1()
{
    printf("\n--------------------------------------\n");
    printf("\n-------- Problem 1 (Sorting) ---------\n");
    printf("\n--------------------------------------\n");
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
    Sort(a, n);
    printf("\nThe elements after sorting : ");
    print(a, n);
}

void FindRange(int time1[], int enter, int leave)
{
    for (int i = 0; i <= (leave - enter); i++)
    {
        time1[i] = enter + i;
    }
}

int ToFindIntersection(int time1[], int time2[], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (time1[i] == time2[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

int NewFriends(int enter[], int leave[], int n)
{
    int co = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int time1[leave[i] - enter[i] + 1];
        FindRange(time1, enter[i], leave[i]);
        for (int j = i + 1; j < n; j++)
        {
            int time2[leave[j] - enter[j] + 1];
            FindRange(time2, enter[j], leave[j]);
            if (ToFindIntersection(time1, time2, leave[i] - enter[i] + 1, leave[j] - enter[j] + 1))
            {
                co++;
                printf("The Distinct pairs of users who are on the site at the same time are : ");
                printf("( %d,%d )\n", i + 1, j + 1);
            }
        }
    }
    return co;
}

void merge(int a[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = a[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = a[m + 1 + i];
    }
    int i = 0, j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        MergeSort(a, l, m);
        MergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int FindNewFriends(int a[], int b[], int n)
{
    MergeSort(a, 0, n - 1);
    MergeSort(b, 0, n - 1);
    int users = 1;
    int co = 0;
    int i = 1, j = 0;
    while (i < n && j < n)
    {
        if (a[i] <= b[j])
        {
            users += 1;
            if (users > 1)
            {
                co += users - 1;
            }
            i++;
        }
        else
        {
            users -= 1;
            j++;
        }
    }
    return co;
}

void problem2()
{
    printf("\n-----------------------------\n");
    printf("\n---------- Problem 2 --------\n");
    printf("\n-----------------------------\n");
    int n;
    printf("Enter the no of users: ");
    scanf("%d", &n);
    int enter[n], leave[n], u[n];
    printf("Enter the user's Enter Time and Leave Time \n");
    for (int i = 0; i < n; i++)
    {
        printf("User %d : \n", i + 1);
        scanf("%d", &enter[i]);
        scanf("%d", &leave[i]);
        u[i] = i + 1;
    }
    // Problem 2 - (a)
    printf("\nPart A : O(n^2)\n");
    int res = NewFriends(enter, leave, n);
    printf("\nThe no.of Distinct pairs of users who are on the site at the same time is : %d\n", res);

    // Problem 2 - (b)
    printf("\n-----------------------------------------------------\n");
    printf("Part B : Performing O(nlogn) time for the above problem\n");
    printf("\n-----------------------------------------------------\n");
    res = 0;
    res = FindNewFriends(enter, leave, n);
    printf("\nThe no.of Distinct pairs of users who are on the site at the same time is : %d\n", res);
}

int FindMin(int a[], int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[min] > a[i])
        {
            min = i;
        }
    }
    return a[min];
}

int Minimum(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int ToFindMin(int a[], int low, int high)
{
    if (low == high)
    {
        return a[low];
    }
    else
    {
        int mid = (low + high) / 2;
        return Minimum(ToFindMin(a, low, mid), ToFindMin(a, mid + 1, high));
    }
}

void problem3()
{
    printf("\n-----------------------------\n");
    printf("\n---------- Problem 3 --------\n");
    printf("\n-----------------------------\n");
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the %d element :", i + 1);
        scanf("%d", &a[i]);
    }
    printf("\nThe given array is : ");
    print(a, n);

    // Problem 3 - (c)
    printf("\nPart (C) : Finding Minimum : \n");
    clock_t s1=clock();
    printf("\nMinimun of %d items in the array is : %d\n", n, FindMin(a, n));
    clock_t e1=clock();
    printf("Time taken : %f seconds\n", (double)(e1 - s1) / CLOCKS_PER_SEC);

    // Problem 3 - (e)
    printf("\n-------------------------------\n");
    printf("\n Part (E) : Using Recursion to Find Minimum\n");
    printf("\n-------------------------------\n");
    clock_t s2=clock();
    printf("Minimun of %d items in array is : %d\n", n, ToFindMin(a, 0, n - 1));
    clock_t e2=clock();
    printf("Time taken : %f seconds\n", (double)(e2 - s2) / CLOCKS_PER_SEC);

}

int FindLocalMin(int a[], int n, int s, int e)
{
    int m = s + (e + s) / 2;
    if (m > 0 && a[m - 1] < a[m])
    {
        return FindLocalMin(a, n, s, m - 1);
    }
    else if (m > 0 && a[m + 1] > a[m])
    {
        return FindLocalMin(a, n, m + 1, e);
    }
    if ((m == n - 1 || a[m + 1] > a[m]) && (m == 0 || a[m - 1] > a[m]))
    {
        return m;
    }
}

int FindingMin(int n, int a[][n], int midR, int colS, int colE)
{
    int min = a[midR][colS];
    int index = colS;
    for (int i = colS + 1; i < colE; i++)
    {
        if (a[midR][i] < min)
        {
            min = a[midR][i];
            index = i;
        }
    }
    return index;
}

int ToFindLocalMin(int n, int a[][n], int rowS, int rowE, int colS, int colE)
{
    int col1, col2;
    int midR = (rowS + rowE) / 2;
    int minI = FindingMin(n, a, midR, colS, colE);
    if (minI >= (colS + colE) / 2)
    {
        col1 = (colS + colE) / 2;
        col2 = colE;
    }
    else
    {
        col1 = colS;
        col2 = (colS + colE) / 2;
    }
    if (a[midR][minI] < a[midR + 1][minI] && a[midR][minI] < a[midR - 1][minI])
    {
        return a[midR][minI];
    }
    else if (a[midR][minI] > a[midR + 1][minI])
    {
        return ToFindLocalMin(n, a, midR, rowE, col1, col2);
    }
    else
    {
        return ToFindLocalMin(n, a, rowS, midR, col1, col2);
    }
}

void problem4()
{
    printf("\n-----------------------------\n");
    printf("\n---------- Problem 4 --------\n");
    printf("\n-----------------------------\n");
    int n, res;
    printf("Enter the size of the array : ");
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the %d element :", i + 1);
        scanf("%d", &a[i]);
    }
    printf("\nThe given array is : ");
    print(a, n);

    // Problem 4 - (a)
    printf("\nPart A : Finding Local Minimum in the array\n");
    res = FindLocalMin(a, n, 0, n - 1);
    if (res == -1)
    {
        printf("No Local Minimum was found in the given array\n");
    }
    else
    {
        printf("Local Minimum of the given array is : %d\n", a[res]);
    }

    // Problem 4 - (b)
    printf("\nPart B : Finding Local Minimum in the 2D array\n");
    printf("Enter the value of n for nxn square matrix : ");
    scanf("%d", &n);
    int z[n][n];
    printf("Enter the elements of the matrix of %dx%d grid\n", n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &z[i][j]);
        }
    }
    res = ToFindLocalMin(n, z, 0, n, 0, n);
    printf("The Local Minimum of the given matrix is : %d\n", res);
}

int main()
{
    problem1();
    problem2();
    problem3();
    problem4();
}
