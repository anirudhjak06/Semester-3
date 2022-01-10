//This Assignment is done by Anirudh Jakhotia
//Roll No : S20190010007

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct graph
{
    int lead,load;
    char hover[20],hoverdep[5],hoverarr[5];
    struct graph *after;
}Graph_data;

Graph_data *CreateNode(int p, int weight, char label[], char line1[], char line2[])
{
    Graph_data *obj = (Graph_data*)malloc(sizeof(Graph_data));
    obj->lead=p;
    obj->load=weight;
    strcpy(obj->hover,label);
    strcpy(obj->hoverdep,line1);
    strcpy(obj->hoverarr,line2);
    obj->after=NULL;
    return obj;
}

void Insertion(Graph_data *record[],int l,int p,int q,char label[],char line1[],char line2[],int weight)
{
    if(p > l)
    {
        printf("\n--------------------------------------\n");
        printf("Given vertex is not present in the graph\n");
        printf("\n--------------------------------------\n");
        return;
    }
    Graph_data *bef=record[p];
    Graph_data *pre=record[p]->after;
    while(pre!=NULL)
    {
        bef=pre;
        pre=pre->after;
    }
    bef->after=CreateNode(q,weight,label,line1,line2);
}

int Find_Min(int l,int value[],int stayed[])
{
    int least=100000,pos;
    for(int j=0;j<l;j++)
    {
        if(stayed[j]==0 && value[j]<=least)
        {
            least=value[j];
            pos = j;
        }
    }
    return pos;
}

int Summing_time(int line1,int line2)
{
    int a = line1%100,b = line1/100;
    a = a+line2;
    if(a>60)
    {
        a = a%60;
        b+=1;
    }
    if(b>23)
        b=b%23;

    return (b*100+a);
}

void Finding_cheapest_Trip(Graph_data *record[],int l,int k,int r,char hover_d[],char hover_a[])
{
    int stayed[l],value[l],span[l];
    for(int j=0;j<l;j++)
    {
        stayed[j]=0;
        value[j]=100000;
        span[j]=2400;
    }
    value[k]=0;
    span[k]=atoi(hover_d);
    for(int j=0;j<l;j++)
    {
        int min = Find_Min(l,value,stayed);
        Graph_data *pre = record[min]->after;
        stayed[min]=1;
        while(pre!=NULL)
        {
            if(stayed[pre->lead]==0 && span[min] <= atoi(pre->hoverdep) && atoi(pre->hoverarr) <= atoi(hover_a) && value[pre->lead] > value[min]+pre->load)
            {
                value[pre->lead] = value[min] + pre->load;
                span[pre->lead] = Summing_time(atoi(pre->hoverarr),30);
            }
            pre=pre->after;   
        }
    }
    if(value[r]==100000)
    {
        printf("There is no route present between the two stations at that time\n");
    }
    else
    {
        printf("%d\n",value[r]);
    }
}

int main()
{
    char name[100];
    int l;
    FILE* file_p;
    printf("Enter the name of the File : ");
    scanf("%s",name);
    file_p=fopen(name,"r");
    fscanf(file_p, "%d", &l);
    Graph_data *record[l];
    for(int i=0;i<l;i++)
    {
        record[i]=CreateNode(i+1,0,"","0000","0000");
    }
    int mm;
    fscanf(file_p,"%d", &mm);
    char line1[5],line2[5];
    int p,q,r; 
    for(int j=0;j<mm;j++)
    {
        fscanf(file_p,"%d %d %s %s %s %d",&p,&q,line1,line2,name,&r);
        Insertion(record,l,p-1,q-1,name,line1,line2,r);
    }
    int nn;
    fscanf(file_p, "%d", &nn);
    printf("Printing the cheapest trip for the given queries : \n"); 
    for(int j=0;j<nn;j++)
    {
       fscanf(file_p,"%d %d %s %s",&p,&q,line1,line2);
       Finding_cheapest_Trip(record,l,p-1,q-1,line1,line2); 
    }
    fclose(file_p);
    printf("\n---------------------------------------------------\n");
    printf("\nThank You! I hope you have got the required details\n");
    printf("\n---------------------------------------------------\n");
    return 0;
}