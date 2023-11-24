#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    int f;
    struct node *next;
} Node;
void mfu(int);
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
    printf("how many frames=");
    scanf("%d", &m);
    printf("Enter the no.of pages=\t");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the page no=%d\t", i);
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++)
    {
        mfu(a[i]);
        printf("\n");
        print();
    }
    printf("\n no.of page fault=%d", pgfault);
    return 0;
}
void mfu(int page)
{
    Node *ptr, *temp, *MFUnode, *prev, *prevptr;
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
        if (cnt < m)
        {
            ptr = (Node *)malloc(sizeof(Node));
            ptr->data = page;
            ptr->next = NULL;
            ptr->f = 1;
            if (start == NULL)
                start = last = ptr;
            else
            {
                last->next = ptr;
                last = ptr;
            }
            cnt++;
        }
        else
        {
            MFUnode = start;
            temp = start;
            prev = start;
            while (temp != NULL)
            {
                if (MFUnode->f < temp->f)
                {
                    MFUnode = temp;
                    prevptr = prev;
                }
                prev = temp;
                temp = temp->next;
            }
            MFUnode->data = page;
            MFUnode->f = 1;
            if (MFUnode == last)
                return;
            if (MFUnode == start)
            {
                start = start->next;
                MFUnode->next = NULL;
                last->next = MFUnode;
                last = MFUnode;
            }
            else
            {
                prevptr->next = MFUnode->next;
                MFUnode->next = NULL;
                last->next = MFUnode;
                last = MFUnode;
            }
        }
    }
}