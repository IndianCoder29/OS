#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    char name[20];
    int bt,at,wt,tat;  
    int remaining_time;  // Remaining Burst Time
    int completed;  // Flag to check if the process has completed execution
    int start, end;  // Start and End times for the Gantt chart
};

void take_input(struct Process p[], int n, int time_quantum) {
    printf("Enter Process details:\nName\tBT\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d", p[i].name, &p[i].bt);
        p[i].remaining_time = p[i].bt;
        p[i].completed = 0;
    }
}

void round_robin(struct Process p[], int n, int time_quantum) {
    int current_time = 0;

    printf("\nGrantt Chart => %d - ", current_time);

    while (1) {
        int all_completed = 1;  // Flag to check if all processes are completed

        for (int i = 0; i < n; i++) {
            if (!p[i].completed) {
                all_completed = 0;

                // Execute the process for the time quantum or remaining time, whichever is smaller
                int execute_time = (p[i].remaining_time < time_quantum) ? p[i].remaining_time : time_quantum;

                p[i].remaining_time -= execute_time;
                p[i].start = current_time;
                p[i].end = current_time + execute_time;

                printf("%s - %d - ", p[i].name, p[i].end);

                current_time = p[i].end;

                if (p[i].remaining_time == 0) {
                    // Process completed
                    p[i].completed = 1;
                }
            }
        }

        if (all_completed) {
            // All processes have completed
            break;
        }
    }

    printf("\n");
}

void print_output(struct Process p[], int n) {
    printf("\nProcess\tStart\tEnd\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].end = p[i].start + p[i].bt;  // Update end time for non-preemptive case
        p[i].tat = p[i].end;  // Turnaround time for round robin is the same as end time
        p[i].wt = p[i].tat - p[i].bt;

        printf("%s\t%d\t%d\t%d\t%d\n", p[i].name, p[i].start, p[i].end, p[i].tat, p[i].wt);
    }

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("Avg. TAT : %f\nAvg. WT : %f\n", avg_tat, avg_wt);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    struct Process p[MAX_PROCESSES];

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    take_input(p, n, time_quantum);
    round_robin(p, n, time_quantum);
    print_output(p, n);

    return 0;
}
