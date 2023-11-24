#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int frequency;
    struct node *next;
} Node;

void lfu(int page);
void print();
Node *start = NULL, *last = NULL;
int pgfault = 0, m, n;
int a[80];

int main() {
    int i;
    printf("How many frames=");
    scanf("%d", &m);
    printf("Enter the number of pages:\t");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter the page no=%d\t", i);
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        lfu(a[i]);
        printf("\n");
        print();
    }

    printf("\nNumber of page faults: %d\n", pgfault);
    return 0;
}

void lfu(int page) {
    Node *ptr, *temp, *lfuNode, *prev, *prevPtr;
    int found = 0;
    static int cnt = 0;

    for (ptr = start; ptr != NULL; ptr = ptr->next) {
        if (ptr->data == page) {
            ptr->frequency++;
            found = 1;
        }
    }

    if (found == 0) {
        pgfault++;

        if (cnt < m) {
            ptr = (Node *)malloc(sizeof(Node));
            ptr->data = page;
            ptr->next = NULL;
            ptr->frequency = 1;

            if (start == NULL)
                start = last = ptr;
            else {
                last->next = ptr;
                last = ptr;
            }
            cnt++;
        } else {
            lfuNode = start;
            temp = start;
            prev = start;

            while (temp != NULL) {
                if (lfuNode->frequency > temp->frequency) {
                    lfuNode = temp;
                    prevPtr = prev;
                }
                prev = temp;
                temp = temp->next;
            }

            lfuNode->data = page;
            lfuNode->frequency = 1;

            if (lfuNode == last)
                return;

            if (lfuNode == start) {
                start = start->next;
                lfuNode->next = NULL;
                last->next = lfuNode;
                last = lfuNode;
            } else {
                prevPtr->next = lfuNode->next;
                lfuNode->next = NULL;
                last->next = lfuNode;
                last = lfuNode;
            }
        }
    }
}

void print() {
    Node *ptr;
    for (ptr = start; ptr != NULL; ptr = ptr->next) {
        printf("%d\t%d\t", ptr->data, ptr->frequency);
    }
    printf("\n");
}
