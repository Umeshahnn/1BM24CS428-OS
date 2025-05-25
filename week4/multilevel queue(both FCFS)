#include <stdio.h>

#define MAX 10

// Define a struct for Process
typedef struct {
    int id;      // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int pri;     // Priority
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
    int ct;      // Completion Time
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
        printf("Priority (Lower value = Higher priority): ");
        scanf("%d", &p[i].pri);

        // Assign to Queue 1 or Queue 2 based on priority
        if (p[i].pri <= 3) {
            q1[q1_count++] = p[i]; // High priority queue
        } else {
            q2[q2_count++] = p[i]; // Low priority queue
        }
    }

    // Sort both queues by Arrival Time (FCFS)
    sort_by_arrival(q1, q1_count);
    sort_by_arrival(q2, q2_count);

    // Execute Queue 1 (Higher Priority, FCFS)
    printf("\nExecuting Queue 1 (Higher Priority, FCFS):\n");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < q1_count; i++) {
        if (total_time < q1[i].at)
            total_time = q1[i].at;  // Ensure CPU starts at the right time

        q1[i].wt = total_time - q1[i].at;
        q1[i].tat = q1[i].wt + q1[i].bt;
        q1[i].ct = total_time + q1[i].bt;
        total_wt += q1[i].wt;
        total_tat += q1[i].tat;
        total_time += q1[i].bt;

        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                q1[i].id, q1[i].at, q1[i].bt, q1[i].ct, q1[i].wt, q1[i].tat);
    }

    // Execute Queue 2 (Lower Priority, FCFS)
    printf("\nExecuting Queue 2 (Lower Priority, FCFS):\n");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < q2_count; i++) {
        if (total_time < q2[i].at)
            total_time = q2[i].at;  // Ensure CPU starts at the right time

        q2[i].wt = total_time - q2[i].at;
        q2[i].tat = q2[i].wt + q2[i].bt;
        q2[i].ct = total_time + q2[i].bt;
        total_wt += q2[i].wt;
        total_tat += q2[i].tat;
        total_time += q2[i].bt;

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
