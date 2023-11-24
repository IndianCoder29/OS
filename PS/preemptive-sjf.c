#include <stdio.h>
#include <limits.h>

struct Process {
    char name[20];
    int bt, at, tat, wt, start, end;
    int remaining_time;
    int completed; // Flag to check if the process has completed execution
};

void take_input(struct Process p[], int n) {
    printf("Enter Process details:\nName\tBT\tAT\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].name, &p[i].bt, &p[i].at);
        p[i].remaining_time = p[i].bt;
        p[i].completed = 0;
    }
}

int find_shortest_job(struct Process p[], int n, int current_time) {
    int min_index = -1;
    int min_bt = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && !p[i].completed && p[i].remaining_time < min_bt) {
            min_bt = p[i].remaining_time;
            min_index = i;
        }
    }

    return min_index;
}

void calculate_times(struct Process p[], int n) {
    int current_time = 0;

    while (1) {
        int index = find_shortest_job(p, n, current_time);

        if (index == -1) {
            // No valid process found to execute
            break;
        }

        // Execute the process for 1 unit of time
        p[index].remaining_time--;

        if (p[index].remaining_time == 0) {
            // Process completed
            p[index].completed = 1;
            p[index].end = current_time + 1;
            p[index].tat = p[index].end - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
        }

        current_time++;
    }
}

void print_output(struct Process p[], int n) {
    printf("\nProcess\tStart\tEnd\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].end, p[i].tat, p[i].wt);
    }

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("Avg. TAT : %f\nAvg. WT : %f", avg_tat, avg_wt);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    take_input(p, n);
    calculate_times(p, n);
    print_output(p, n);

    return 0;
}
