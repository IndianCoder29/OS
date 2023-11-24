#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} Node;
Node *start = NULL, *last = NULL;
int pgfault = 0, m, n;
int a[80];
main()
{
    int i;
    printf("\n how many frames=");
    scanf("%d", &m);
    printf("\n\n Enter the no.of page=");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\n\n Enter the page no=%d\t", i);
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++)
    {
        if (search(a[i]) == 0)
        {
            addlist(a[i]);
            pgfault++;
            printf("\n page fault occur");
            print();
        }
        printf("\n");
        print();
    }
    printf("\n no of page fault=%d", pgfault);
}
int search(int page)
{
    Node *ptr, *prev;
    for (ptr = prev = start; ptr != NULL; prev = ptr, ptr = ptr->next)
        if (ptr->data == page)
        {
            if (ptr == start)
                return 1;
            if (ptr->next == NULL)
            {
                prev->next = NULL;
                ptr->next = start;
                start = ptr;
            }
            else
            {
                prev->next = ptr->next;
                ptr->next = start;
                start = ptr;
            }
            return 1;
        }
    return 0;
}
void print()
{
    Node *ptr;
    for (ptr = start; ptr != NULL; ptr = ptr->next)
        printf("%d\t", ptr->data);
    printf("\n");
}
void addlist(int page)
{
    Node *ptr = NULL;
    static int cnt = 0;
    ptr = (Node *)malloc(sizeof(Node));
    ptr->data = page;
    ptr->next = NULL;
    if (start == NULL)
    {
        start = ptr;
        cnt++;
    }
    else if (cnt < m)
    {
        ptr->next = start;
        start = ptr;
        cnt++;
    }
    else
    {
        start = start->next;
        ptr->next = start;
        start = ptr;
    }
}
