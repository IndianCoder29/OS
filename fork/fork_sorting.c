#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void bubblesort(int arr[30], int n);
void insertionsort(int arr[30], int n);

void bubbleSortRecursive(int arr[], int n) {
    if (n == 1)
        return;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            // swap
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }

    bubbleSortRecursive(arr, n - 1);
}

void insertionSortRecursive(int arr[], int n) {
    if (n <= 1)
        return;

    insertionSortRecursive(arr, n - 1);

    int last = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }

    arr[j + 1] = last;
}

void fork1() {
    int arr[25], n, i, status;
    printf("\nEnter the number of values in array: ");
    scanf("%d", &n);

    printf("\nEnter the array elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int pid = fork();

    if (pid == 0) {
        sleep(10);
        printf("Child process PID = %d\n", getpid());
        printf("\nElements Sorted Using Insertion Sort (Recursive):\n");
        insertionSortRecursive(arr, n);
        for (i = 0; i < n; i++)
            printf("%d, ", arr[i]);
        printf("\b\nParent process id = %d\n", getppid());
        system("ps -x");
    } else {
        printf("\nParent process PID = %d\n", getppid());
        printf("Elements Sorted Using Bubble Sort (Recursive):\n");
        bubbleSortRecursive(arr, n);
        for (i = 0; i < n; i++)
            printf("%d, ", arr[i]);
        printf("\n\n\n");
    }
}

int main() {
    fork1();
    return 0;
}