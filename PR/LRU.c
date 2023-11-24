#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    int f;
    struct node *next;
} Node;
void lru(int);
Node *start = NULL, *last = NULL;
int pgfault = 0, m, n;
int a[80];
void print()
{
    Node *ptr;
    for (ptr = start; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\t%d\t", ptr->data, ptr->f);
    }
    printf("\n");
}
int main()
{
    int i;
    printf("How many frames:");
    scanf("%d", &m);
    printf("Enter the no of pages:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the page no %d\t", i);
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++)
    {
        lru(a[i]);
        printf("\n");
        print();
    }
    printf("Number of page fault : %d", pgfault);
    return 0;
}
void lru(int page)
{
    Node *ptr, *temp, *LRUnode;
    int found = 0;
    static int cnt = 0;
    for (ptr = start; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->data == page)
        {
            ptr->f = ptr->f + 1;
            found = 1;
        }
    }
    if (found == 0)
    {
        pgfault++;
        if (start == NULL)
        {
            ptr = (Node *)malloc(sizeof(Node));
            ptr->data = page;
            ptr->next = NULL;
            ptr->f = 1;
            start = last = ptr;
            cnt++;
        }
        else if (cnt < m)
        {
            ptr = (Node *)malloc(sizeof(Node));
            ptr->data = page;
            ptr->next = NULL;
            ptr->f = 1;
            last->next = ptr;
            last = ptr;
            cnt++;
        }
        else
        {
            LRUnode = start;
            temp = start;
            while (temp != NULL)
            {
                if (LRUnode->f > temp->f)
                {
                    LRUnode = temp;
                }
                temp = temp->next;
            }
            LRUnode->data = page;
            LRUnode->f = 1;
        }
    }
    printf("\ncount = %d", cnt);
}