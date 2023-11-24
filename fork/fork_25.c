#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1; // Key not found
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    int pid = fork();

    if (pid == 0) {
        // Child process
        char *args[] = {"binarySearchProgram", NULL};
        execve("./binarySearchProgram", args, NULL);
    } else {
        // Parent process
        bubbleSort(arr, n);

        printf("Sorted array in parent process: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}