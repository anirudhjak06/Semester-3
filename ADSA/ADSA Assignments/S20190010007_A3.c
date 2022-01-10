//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct emp
{
    char name[20];
    int level;
    int visited;
    struct emp *colleague;
    struct emp *mate;
}Emp;

Emp *CreateNode(char n[],int l)
{
    Emp *t = (Emp*)malloc(sizeof(Emp));
    strcpy(t->name,n);
    t->level=l;
    t->colleague=NULL;
    t->mate=NULL;
    t->visited=0;
    return t;
}

typedef struct q
{
    Emp *emp;
    struct q *next;
}Q;

Q *front=NULL;
Q *rear=NULL;

Q *new(Emp *e)
{
    Q *t = (Q*)malloc(sizeof(Q));
    t->emp=e;
    t->next=NULL;
    return t;
}

void In(Emp* e)
{
    if(e==NULL || e->visited!=0)
    {
        return;
    }
    e->visited=1;
    Q *t = new(e);
    if(front==NULL)
    {
        front=t;
        rear=t;
    }
    else
    {
        rear->next=t;
        rear=t;
    } 
}

Q *Out()
{
    if(front==NULL)
    {
        return NULL;
    }
    else if(front==rear)
    {
        Q *t=front;
        front=NULL;
        rear=NULL;
        t->emp->visited=0;
        return t;
    }
    else
    {
        Q *t = front;
        front=front->next;
        t->next=NULL;
        t->emp->visited=0;
        return t;   
    }
}

void InColleagues(Emp *e)
{
    while(e!=NULL)
    {
        In(e);
        e=e->colleague;
    }
}

void printEmp(Emp *pre)
{
    while(pre!=NULL)
    {
        InColleagues(pre);
        Q *t = Out();
        printf("|\t%s\t|\t%d\t|\n",t->emp->name,t->emp->level);
        In(t->emp->mate);
        if(front==NULL)
        {
            pre=NULL;
        }
        else
        {    
            pre=front->emp;
        }
    }
}

Emp* findEmp(Emp *pre,char S[])
{
    Emp *t1,*t2;
    if(pre==NULL)
    {
        return NULL;
    }
    else
    {
        if(strcmp(S,pre->name)==0)
        {
            return pre;
        }
        else
        {
            t1 = findEmp(pre->colleague,S);
            t2 = findEmp(pre->mate,S);
            if(t1!=NULL)
            {
                return t1;
            }
            else if(t2!=NULL)
            {
                return t2;
            }
            else
            {
                return NULL;
            }
        }
    }
}

Emp *parent;
Emp *left;

void ParentEmp(Emp *root,char S[])
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        if(root->mate!=NULL)
        {
            Emp *t3 = root->mate;
            while(t3!=NULL)
            {
                if(strcmp(t3->name,S)==0)
                {
                    parent=root;
                    break;
                }
                t3 = t3->colleague;
            }
        }
        if(root->colleague!=NULL && strcmp(S,root->colleague->name)==0)
        {
            left = root;
        }
        if(strcmp(S,root->name)==0)
        {
            return;
        }
        ParentEmp(root->colleague,S);
        ParentEmp(root->mate,S);
    }
}

void addEmp(Emp *head,char S[],char S1[])
{
    Emp *t=head;
    Emp *parent = findEmp(t,S1);
    if(parent==NULL)
    {
        printf("\n-----------------------------------------\n");
        printf("ERROR : Employee of name %s does not exist",S1);
        printf("\n-----------------------------------------\n");
        return;
    }
    Emp *pre = parent->mate;
    if(pre==NULL)
    {
        parent->mate=CreateNode(S,parent->level+1);
        printf("Employee %s added to the list \n",S);
        return;
    }  
    Emp *prev;
    while(pre!=NULL)
    {
        prev=pre;
        pre=pre->colleague;
    }
    prev->colleague = CreateNode(S,parent->level+1);
    printf("Employee %s added to the list \n",S);
    //printf("Employee %s Added \n",S);
}

void deleteEmp(Emp *head,char S[],char S1[])
{
    parent=NULL;
    left=NULL;
    Emp *t = head;
    ParentEmp(t,S);
    t=parent->mate;
    Emp *pre1 = findEmp(t,S1); 
    t=parent->mate;
    Emp *pre2 = findEmp(t,S); 
    if(left==NULL && pre2->colleague==NULL)
    {
        printf("\n-------------------------------------------------------\n");
        printf("The Employee %s cannot be deleted\n");
        printf("NOTE : As there is no one else to take the responsibility",S);
        printf("\n-------------------------------------------------------\n");
        return;
    }
    if(pre1==NULL)
    {
        printf("\n------------------------------------------\n");
        printf("The Employee %s can be deleted\n");
        printf("NOTE : As there is no employee of name %s",S,S1);
        printf("\n------------------------------------------\n");
        return;
    } 
    Emp *pre = pre1->mate;
    if(pre==NULL)
    {
        pre1->mate=pre2->mate;
        if(left==NULL && parent!=NULL)
        {
            parent->mate = pre2->colleague;
        }
        else if(left!=NULL)
        {
            left->colleague=pre2->colleague;
        }
        free(pre2);
        printf("Employee %s deleted from the list\n",S);
    }
    else
    {
        Emp *prev;
        while(pre!=NULL)
        {
            prev=pre;
            pre=pre->colleague;
        }
        prev->colleague = pre2->mate;
        if(left==NULL)
        {
            parent->mate = pre2->colleague;
        }
        else if(left!=NULL)
        {
            left->colleague=pre2->colleague;
        }
        free(pre2);
        printf("Employee %s deleted from the list\n",S);
    }     
}

void lowestCommonBoss(Emp *head,char S[],char S1[])
{
    Emp *t;
    t=head;
    parent=NULL;
    ParentEmp(t,S);
    Emp *p = parent;
    t=head;
    parent=NULL;
    ParentEmp(t,S1);
    Emp *q = parent;
    if(strcmp(p->name,q->name)==0)
    {
        printf("The Lowest Common boss is %s of LEVEL : %d\n",p->name,p->level);
    }
    else if(strcmp(p->name,S1)==0)
    {
       printf("The Lowest Common boss is %s of LEVEL : %d\n",q->name,q->level); 
    }
    else if(strcmp(q->name,S)==0)
    {
        printf("The Lowest Common boss is %s of LEVEL : %d\n",p->name,p->level);
    }
    else
    {
        parent=NULL;
        if(p->level >= q->level)
        {
            t=head;
            ParentEmp(t,q->name);
            p=parent;
            printf("The Lowest Common boss is %s of LEVEL : %d\n",p->name,p->level);
        }
        else
        {
            t=head;
            ParentEmp(t,p->name);
            p=parent;
            printf("The Lowest Common boss is %s of LEVEL : %d\n",p->name,p->level);
        }
    }
}

int main()
{
    int ch;
    char S[20];
    char S1[20];
    Emp *head=NULL;
    Emp *temp;
    printf("Enter the name of CEO (which will be at level 1) : ");
    scanf("%s",S);
    head = CreateNode(S,1);
    while(1)
    {
        printf("\n---------------------\n");
        printf("\tMENU");
        printf("\n---------------------\n");
        printf("1- Add Employee\n");
        printf("2- Delete Employee\n");
        printf("3- Lowest Common Boss\n");
        printf("4 -Print Employee\n");
        printf("5- Exit\n");
        printf("\n---------------------\n");
        printf("Please select appropiate no. for your task : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter the name of the new employee S : ");
                scanf("%s",S);
                printf("NOTE : (S will work under S') \n");
                printf("Enter the name of the existing employee S' : ");
                scanf("%s",S1);
                addEmp(head,S,S1);
                //printf("Employee %s Added \n",S);
                break;
            case 2: 
                printf("Enter the name of the employee S you want to remove : ");
                scanf("%s",S);
                printf("NOTE : (S,S' are at same level) \n");
                printf("Enter the name of the existing employee S' : ");
                scanf("%s",S1);
                deleteEmp(head,S,S1);
                break;
            case 3:
                printf("Enter the name of the employee S : ");
                scanf("%s",S);
                printf("NOTE : (S' also works in same company) \n"); 
                printf("Enter the name of the employee S': ");
                scanf("%s",S1);
                lowestCommonBoss(head,S,S1);
                break;
            case 4:
                temp=head;
                printf("Printing the details of the Employees : \n");
                //printf("|\t%s\t|\t%d\t|\n",t->emp->name,t->emp->level);
                printf("\n|---------------|---------------|");
                printf("\n|      NAME\t|\tLEVEL\t|\n");
                printf("---------------------------------\n");
                printEmp(temp);
                printf("|---------------|---------------|");
                printf("\n\n");
                break;
            case 5:
                printf("\n---------------------------------------------------\n");
                printf("\nThank You! I hope you have got the required details\n");
                printf("\n---------------------------------------------------\n");
                exit(0);
            default :
                printf("\n--------------------------------\n");
                printf("You have entered an invalid number\n");
                printf("\n--------------------------------\n");
                break;        
        }
    }
}