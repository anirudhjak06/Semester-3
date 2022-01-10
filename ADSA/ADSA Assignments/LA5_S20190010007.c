#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CHAR_SIZE 26

struct DefineTrie
{
    int isLeaf;
    struct DefineTrie *character[CHAR_SIZE];
};

struct DefineTrie *NewTrie()
{
    struct DefineTrie *node = (struct DefineTrie *)malloc(sizeof(struct DefineTrie));
    node->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }
    return node;
}

void Insertion(struct DefineTrie *head, char *str)
{
    struct DefineTrie *curr = head;
    while (*str)
    {
        if (curr->character[*str - 'a'] == NULL)
        {
            curr->character[*str - 'a'] = NewTrie();
        }
        curr = curr->character[*str - 'a'];
        str++;
    }
    curr->isLeaf = 1;
}

int Searching(struct DefineTrie *head, char *str)
{
    if (head == NULL)
    {
        return 0;
    }
    struct DefineTrie *curr = head;
    while (*str)
    {
        curr = curr->character[*str - 'a'];
        if (curr == NULL)
        {
            return 0;
        }
        str++;
    }
    return curr->isLeaf;
}

int ExtendedTrie(struct DefineTrie *curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i])
        {
            return 1;
        }
    }
    return 0;
}

int Deletion(struct DefineTrie **curr, char *str)
{
    if (*curr == NULL)
    {
        return 0;
    }
    if (*str)
    {
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            Deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!ExtendedTrie(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    if (*str == '\0' && (*curr)->isLeaf)
    {
        if (!ExtendedTrie(*curr))
        {
            free(*curr);
            (*curr) = NULL;
            return 1;
        }
        else
        {
            (*curr)->isLeaf = 0;
            return 0;
        }
    }
    return 0;
}

int main()
{
    struct DefineTrie *head = NewTrie();
    char fn[100],word[200];
    printf("Enter the File Name with extension\n");
    gets(fn);
    FILE *fp = fopen(fn, "r");
    int index = 0,c;
    if (fp == NULL)
    {
        printf("\n------------\n");
        printf("File not Found\n");
        printf("\n------------\n");
    }
    while ((c = fgetc(fp)) != EOF)
    {
        char ch = (char)c;
        if (isalpha(ch))
        {
            word[index++] = ch;
        }
        else
        {
            word[index] = '\0';
            index = 0;
            Insertion(head, word);
        }
    }
    /*char* s;
    while (fscanf(fp, "%s", s) != EOF) {
        Insertion(head, s);
    }*/
    fclose(fp);
    char b[20];
    int data;
    while (1)
    {
        printf("Please select appropiate no. for your task\n");
        printf("\n---------------------\n");
        printf("1- To Perform Insertion\n");
        printf("2- To perform Searching\n");
        printf("3- To perform Deletion\n");
        printf("4- To Quit\n");
        printf("\n---------------------\n");
        scanf("%d", &data);
        switch (data)
        {
            case 1:
                printf("Enter any string to Insert : ");
                scanf("%s", b);
                Insertion(head, b);
                break;
            case 2:
                printf("Enter any string to Search : ");
                scanf("%s", b);
                if (Searching(head, b) == 1)
                {
                    printf("\n-----------------------\n");
                    printf("The string %s is Found\n", b);
                    printf("\n-----------------------\n");
                }
                else if (Searching(head, b) == 0)
                {
                    printf("\n---------------------------\n");
                    printf("The string %s is not Found\n", b);
                    printf("\n---------------------------\n");
                }
                break;
            case 3:
                printf("Enter any string to Delete : ");
                scanf("%s", b);
                Deletion(&head, b);
                printf("The string %s is deleted\n", b);
                break;
            case 4:
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
        printf("\n");
    }
}
