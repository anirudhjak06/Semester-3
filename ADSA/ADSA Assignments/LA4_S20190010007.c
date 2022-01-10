#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

enum NodeC
{
    RED,
    BLACK
};

struct RedBlackN
{
    int data, color;
    struct RedBlackN *link[2];
};

struct RedBlackN *root = NULL;

struct RedBlackN *Create(int key)
{
    struct RedBlackN *new;
    new = (struct RedBlackN *)malloc(sizeof(struct RedBlackN));
    new->data = key;
    new->color = RED;
    new->link[0] = new->link[1] = NULL;
    return new;
}

void Delete(int data)
{
    struct RedBlackN *a[98], *ptr, *xPtr, *yPtr;
    struct RedBlackN *pPtr, *qPtr, *rPtr;
    int b[98], k = 0, diff, i;
    enum NodeC color;

    if (!root)
    {
        printf("\n----------------\n");
        printf("Tree not available\n");
        printf("\n----------------\n");
        return;
    }

    ptr = root;
    while (ptr != NULL)
    {
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
        a[k] = ptr;
        b[k++] = diff;
        ptr = ptr->link[diff];
    }

    if (ptr->link[1] == NULL)
    {
        if ((ptr == root) && (ptr->link[0] == NULL))
        {
            free(ptr);
            root = NULL;
        }
        else if (ptr == root)
        {
            root = ptr->link[0];
            free(ptr);
        }
        else
        {
            a[k - 1]->link[b[k - 1]] = ptr->link[0];
        }
    }
    else
    {
        xPtr = ptr->link[1];
        if (xPtr->link[0] == NULL)
        {
            xPtr->link[0] = ptr->link[0];
            color = xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = color;

            if (ptr == root)
            {
                root = xPtr;
            }
            else
            {
                a[k - 1]->link[b[k - 1]] = xPtr;
            }

            b[k] = 1;
            a[k++] = xPtr;
        }
        else
        {
            i = k++;
            while (1)
            {
                b[k] = 0;
                a[k++] = xPtr;
                yPtr = xPtr->link[0];
                if (!yPtr->link[0])
                    break;
                xPtr = yPtr;
            }

            b[i] = 1;
            a[i] = yPtr;
            if (i > 0)
                a[i - 1]->link[b[i - 1]] = yPtr;

            yPtr->link[0] = ptr->link[0];

            xPtr->link[0] = yPtr->link[1];
            yPtr->link[1] = ptr->link[1];

            if (ptr == root)
            {
                root = yPtr;
            }

            color = yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = color;
        }
    }

    if (k < 1)
        return;

    if (ptr->color == BLACK)
    {
        while (1)
        {
            pPtr = a[k - 1]->link[b[k - 1]];
            if (pPtr && pPtr->color == RED)
            {
                pPtr->color = BLACK;
                break;
            }

            if (k < 2)
                break;

            if (b[k - 2] == 0)
            {
                rPtr =a[k - 1]->link[1];

                if (!rPtr)
                    break;

                if (rPtr->color == RED)
                {
                    a[k - 1]->color = RED;
                    rPtr->color = BLACK;
                    a[k - 1]->link[1] = rPtr->link[0];
                    rPtr->link[0] = a[k- 1];

                    if (a[k - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        a[k - 2]->link[b[k - 2]] = rPtr;
                    }
                    b[k] = 0;
                    a[k] = a[k - 1];
                    a[k - 1] = rPtr;
                    k++;

                    rPtr = a[k - 1]->link[1];
                }

                if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
                    (!rPtr->link[1] || rPtr->link[1]->color == BLACK))
                {
                    rPtr->color = RED;
                }
                else
                {
                    if (!rPtr->link[1] || rPtr->link[1]->color == BLACK)
                    {
                        qPtr = rPtr->link[0];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->link[0] = qPtr->link[1];
                        qPtr->link[1] = rPtr;
                        rPtr = a[k - 1]->link[1] = qPtr;
                    }
                    rPtr->color = a[k - 1]->color;
                    a[k - 1]->color = BLACK;
                    rPtr->link[1]->color = BLACK;
                    a[k - 1]->link[1] = rPtr->link[0];
                    rPtr->link[0] = a[k - 1];
                    if (a[k - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        a[k - 2]->link[b[k - 2]] = rPtr;
                    }
                    break;
                }
            }
            else
            {
                rPtr = a[k - 1]->link[0];
                if (!rPtr)
                    break;

                if (rPtr->color == RED)
                {
                    a[k - 1]->color = RED;
                    rPtr->color = BLACK;
                    a[k - 1]->link[0] = rPtr->link[1];
                    rPtr->link[1] = a[k - 1];

                    if (a[k - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        a[k - 2]->link[b[k - 2]] = rPtr;
                    }
                    b[k] = 1;
                    a[k] = a[k - 1];
                    a[k - 1] = rPtr;
                    k++;

                    rPtr = a[k - 1]->link[0];
                }
                if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
                    (!rPtr->link[1] || rPtr->link[1]->color == BLACK))
                {
                    rPtr->color = RED;
                }
                else
                {
                    if (!rPtr->link[0] || rPtr->link[0]->color == BLACK)
                    {
                        qPtr = rPtr->link[1];
                        rPtr->color = RED;
                        qPtr->color = BLACK;
                        rPtr->link[1] = qPtr->link[0];
                        qPtr->link[0] = rPtr;
                        rPtr = a[k - 1]->link[0] = qPtr;
                    }
                    rPtr->color = a[k - 1]->color;
                    a[k - 1]->color = BLACK;
                    rPtr->link[0]->color = BLACK;
                    a[k - 1]->link[0] = rPtr->link[1];
                    rPtr->link[1] = a[k - 1];
                    if (a[k - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        a[k - 2]->link[b[k - 2]] = rPtr;
                    }
                    break;
                }
            }
            k--;
        }
    }
}

void Insert(int data)
{
    struct RedBlackN *a[98], *ptr, *new, *xPtr, *yPtr;
    int b[98], k= 0, i;
    ptr = root;
    if (!root)
    {
        root = Create(data);
        return;
    }

    a[k] = root;
    b[k++] = 0;
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            printf("\n----------------------\n");
            printf("Duplicates Not Allowed!!\n");
            printf("\n----------------------\n");
            return;
        }
        i = (data - ptr->data) > 0 ? 1 : 0;
        a[k] = ptr;
        ptr = ptr->link[i];
        b[k++] = i;
    }
    a[k - 1]->link[i] = new = Create(data);
    while ((k >= 3) && (a[k - 1]->color == RED))
    {
        if (b[k - 2] == 0)
        {
            yPtr = a[k - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED)
            {
                a[k - 2]->color = RED;
                a[k - 1]->color = yPtr->color = BLACK;
                k = k - 2;
            }
            else
            {
                if (b[k - 1] == 0)
                {
                    yPtr = a[k - 1];
                }
                else
                {
                    xPtr = a[k - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    a[k - 2]->link[0] = yPtr;
                }
                xPtr = a[k - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    a[k - 3]->link[b[k - 3]] = yPtr;
                }
                break;
            }
        }
        else
        {
            yPtr = a[k - 2]->link[0];
            if ((yPtr != NULL) && (yPtr->color == RED))
            {
                a[k - 2]->color = RED;
                a[k - 1]->color = yPtr->color = BLACK;
                k-=2;
            }
            else
            {
                if (b[k - 1] == 1)
                {
                    yPtr = a[k - 1];
                }
                else
                {
                    xPtr = a[k - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    a[k- 2]->link[1] = yPtr;
                }
                xPtr = a[k - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    a[k - 3]->link[b[k - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
}

int Search(int key)
{
    struct RedBlackN *temp=root;
    int diff;
    while(temp!=NULL)
    {
        diff=key-temp->data;
        if(diff>0)
        {
            temp=temp->link[1];
        }
        else if(diff<0)
        {
            temp=temp->link[0];
        }
        else
        {
            printf("\n--------------------\n");
            printf("\nSearch Element Found!!\n");
            printf("\n--------------------\n");
            return 1;
        }  
    }
    printf("\n--------------------------------------\n");
    printf("\nGiven Data Not Found In Red Black Tree!!\n");
    printf("\n--------------------------------------\n");
    return 0;
}

void InorderT(struct RedBlackN *node)
{
    if (node)
    {
        InorderT(node->link[0]);
        printf("%d -> ", node->data);
        InorderT(node->link[1]);
    }
    return;
}

int main()
{
    while (1)
    {
        printf("Please select appropiate no. for your task\n");
        printf("\n---------------------\n");
        printf("1- To Perform Insertion\n");
        printf("2- To perform Deletion\n");
        printf("3- To perform Searching\n");
        printf("4- To perform Traversal\n");
        printf("5- To Quit\n");
        printf("\n---------------------\n");
        int ch,data;
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                printf("Enter the element to Insert : ");
                scanf("%d", &data);
                Insert(data);
                break;
            case 2:
                printf("Enter the element to Delete : ");
                scanf("%d", &data);
                Delete(data);
                break;
            case 3:
                printf("Enter the element to Search : ");
                scanf("%d", &data);
                Search(data);
                break;    
            case 4:
                InorderT(root);
                printf("\n");
                break;
            case 5:
                printf("\n---------------------------------------------------\n");
                printf("\nThank You! I hope you have got the required details\n");
                printf("\n---------------------------------------------------\n");
                exit(0);
            default:
                printf("\n--------------------------------\n");
                printf("You have entered an invalid number\n");
                printf("\n--------------------------------\n");
                break;
        }   
    }
}