#include <stdio.h>
#include <limits.h>

struct Process {
    char name[20];
    int bt, at, priority, tat, wt, start, end;
    int completed; // Flag to check if the process has completed execution
};

void take_input(struct Process p[], int n) {
    printf("Enter Process details:\nName\tBT\tAT\tPriority\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].name, &p[i].bt, &p[i].at, &p[i].priority);
        p[i].completed = 0;
    }
}

int find_highest_priority(struct Process p[], int n, int current_time) {
    int highest_priority = INT_MAX;
    int highest_priority_index = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && !p[i].completed && p[i].priority < highest_priority) {
            highest_priority = p[i].priority;
            highest_priority_index = i;
        }
    }

    return highest_priority_index;
}

void calculate_times(struct Process p[], int n) {
    int current_time = 0;

    printf("Grantt Chart => %d - ", current_time);

    for (int i = 0; i < n; i++) {
        int index = find_highest_priority(p, n, current_time);

        if (index == -1) {
            // No valid process found to execute
            break;
        }

        p[index].start = current_time;
        p[index].end = current_time + p[index].bt;
        p[index].completed = 1;
        p[index].tat = p[index].end - p[index].at;
        p[index].wt = p[index].tat - p[index].bt;

        printf("%s - %d - ", p[index].name, p[index].end);

        current_time = p[index].end;
    }

    printf("\n");
}

void print_output(struct Process p[], int n) {
    printf("\nProcess\tStart\tEnd\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].start, p[i].end, p[i].tat, p[i].wt);
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
