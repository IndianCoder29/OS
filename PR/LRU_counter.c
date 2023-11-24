#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int counter;
    struct node *next;
} Node;

void lru(int page);
void print();
Node *start = NULL, *last = NULL;
int pgfault = 0, m, n;
int a[80];

int main() {
    int i;
    printf("How many frames:");
    scanf("%d", &m);
    printf("Enter the number of pages:");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter the page no %d\t", i);
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        lru(a[i]);
        printf("\n");
        print();
    }

    printf("Number of page faults : %d", pgfault);
    return 0;
}

void lru(int page) {
    Node *ptr, *temp, *lruNode;
    int found = 0;
    static int counter = 1;
    for (ptr = start; ptr != NULL; ptr = ptr->next) {
        if (ptr->data == page) {
            ptr->counter = counter++;
            found = 1;
        }
    }

    if (found == 0) {
        pgfault++;
        if (start == NULL) {
            ptr = (Node *)malloc(sizeof(Node));
            ptr->data = page;
            ptr->next = NULL;
            ptr->counter = counter++;
            start = last = ptr;
        } else if (m > 0) {
            ptr = (Node *)malloc(sizeof(Node));
            ptr->data = page;
            ptr->next = NULL;
            ptr->counter = counter++;
            last->next = ptr;
            last = ptr;
            if (m > 1) {
                m--;
            }
        } else {
            lruNode = start;
            temp = start;
            while (temp != NULL) {
                if (lruNode->counter > temp->counter) {
                    lruNode = temp;
                }
                temp = temp->next;
            }
            lruNode->data = page;
            lruNode->counter = counter++;
        }
    }
}

void print() {
    Node *ptr;
    for (ptr = start; ptr != NULL; ptr = ptr->next) {
        printf("%d\t%d\t", ptr->data, ptr->counter);
    }
    printf("\n");
}