#include <stdio.h>

#define MAX 10
#define TIME_QUANTUM 4  // Define time quantum for Round Robin

// Define a struct for Process
typedef struct {
    int id;      // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
    int ct;      // Completion Time
    int rem_bt;  // Remaining Burst Time for RR
    int queue;   // Queue number (1 or 2)
} Process;

// Function to sort processes by Arrival Time
void sort_by_arrival(Process arr[], int n) {
    int i, j;
    Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i].at > arr[j].at) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function for Round Robin Scheduling
void round_robin(Process q[], int n, int *total_time, int *total_wt, int *total_tat) {
    int i, done = 0;
    int remaining_processes = n;
    while (remaining_processes > 0) {
        done = 0;
        for (i = 0; i < n; i++) {
            if (q[i].rem_bt > 0) {
                done = 1;
                if (q[i].rem_bt > TIME_QUANTUM) {
                    *total_time += TIME_QUANTUM;
                    q[i].rem_bt -= TIME_QUANTUM;
                } else {
                    *total_time += q[i].rem_bt;
                    q[i].ct = *total_time;
                    q[i].tat = q[i].ct - q[i].at;
                    q[i].wt = q[i].tat - q[i].bt;
                    *total_wt += q[i].wt;
                    *total_tat += q[i].tat;
                    q[i].rem_bt = 0;
                    remaining_processes--;
                }
            }
        }
        if (!done) {
            break;
        }
    }
}

// Function for FCFS Scheduling
void fcfs(Process q[], int n, int *total_time, int *total_wt, int *total_tat) {
    int i;
    for (i = 0; i < n; i++) {
        if (*total_time < q[i].at)
            *total_time = q[i].at;  // Ensure CPU starts at the right time

        q[i].wt = *total_time - q[i].at;
        q[i].tat = q[i].wt + q[i].bt;
        q[i].ct = *total_time + q[i].bt;
        *total_wt += q[i].wt;
        *total_tat += q[i].tat;
        *total_time += q[i].bt;
    }
}

int main() {
    int n, i;
    Process q1[MAX], q2[MAX]; // Two queues for multilevel scheduling
    int q1_count = 0, q2_count = 0;
    int total_time = 0, total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    Process p[MAX];

    // Input process details
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter details for Process[%d]:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        // Ask the user to enter the queue for each process
        printf("Enter Queue (1 for High Priority, 2 for Low Priority): ");
        scanf("%d", &p[i].queue);

        // Assign to Queue 1 or Queue 2 based on user input
        if (p[i].queue == 1) {
            q1[q1_count++] = p[i]; // High priority queue
            q1[q1_count-1].rem_bt = p[i].bt; // Set remaining burst time for RR
        } else if (p[i].queue == 2) {
            q2[q2_count++] = p[i]; // Low priority queue
        } else {
            printf("Invalid queue number. Please enter 1 or 2.\n");
            i--; // Re-enter the process details
        }
    }

    // Sort both queues by Arrival Time (FCFS)
    sort_by_arrival(q1, q1_count);
    sort_by_arrival(q2, q2_count);

    // Execute Queue 1 (Higher Priority, Round Robin)
    printf("\nExecuting Queue 1 (Higher Priority, Round Robin):\n");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    round_robin(q1, q1_count, &total_time, &total_wt, &total_tat);

    for (i = 0; i < q1_count; i++) {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                q1[i].id, q1[i].at, q1[i].bt, q1[i].ct, q1[i].wt, q1[i].tat);
    }

    // Execute Queue 2 (Lower Priority, FCFS)
    printf("\nExecuting Queue 2 (Lower Priority, FCFS):\n");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    fcfs(q2, q2_count, &total_time, &total_wt, &total_tat);

    for (i = 0; i < q2_count; i++) {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                q2[i].id, q2[i].at, q2[i].bt, q2[i].ct, q2[i].wt, q2[i].tat);
    }

    // Calculate averages
    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
