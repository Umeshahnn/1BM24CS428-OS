#include<stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//Non preemptive

void sjfSort(int at[], int bt[], int n) {
   
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (bt[j] > bt[j + 1]) {
                swap(&bt[j], &bt[j + 1]);         
                swap(&at[j], &at[j + 1]);
            }
        }
    }
}

void calcTime(int at[], int bt[], int tat[], int ct[], int rt[], int wt[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
      
        if (time < at[i]) {
            time = at[i];
        }
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];     
        rt[i] = time - at[i];
        time = ct[i];
    }
}

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], tat[n], ct[n], rt[n], wt[n];

    printf("\nEnter the arrival and burst time of each of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d Arrival time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    sjfSort(at, bt, n);

    calcTime(at, bt, tat, ct, rt, wt, n);

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}





/*

#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
} Process;

void calculateTimes(Process proc[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = INT_MAX;

        // Find the shortest job among the arrived and not yet completed processes
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= currentTime && !proc[i].completed && proc[i].bt < minBT) {
                minBT = proc[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++; // No process has arrived yet, so advance time
        } else {
            proc[idx].ct = currentTime + proc[idx].bt;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            proc[idx].completed = 1;
            currentTime = proc[idx].ct;
            completed++;
        }
    }
}

void printProcessDetails(Process proc[], int n) {
    int totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].at,
               proc[i].bt,
               proc[i].ct,
               proc[i].tat,
               proc[i].wt);

        totalWT += proc[i].wt;
        totalTAT += proc[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float) totalWT / n);
    printf("Average Turnaround Time: %.2f\n", (float) totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Arrival Time (AT) for P%d: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Enter Burst Time (BT) for P%d: ", i + 1);
        scanf("%d", &proc[i].bt);
        proc[i].completed = 0;
    }

    calculateTimes(proc, n);
    printProcessDetails(proc, n);

    return 0;
}



*/
