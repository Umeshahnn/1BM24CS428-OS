#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

void rate_monotonic_scheduling(int n, int burst[], int period[]) {
    printf("\nRate Monotonic Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");

    float utilization = 0.0;
    int hyper_period = period[0];

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);
        utilization += (float)burst[i] / period[i];
        if (i > 0)
            hyper_period = lcm(hyper_period, period[i]);
    }

    float bound = n * (pow(2, 1.0 / n) - 1);

    printf("\n%.6f <= %.6f => %s\n", utilization, bound, (utilization <= bound) ? "Schedulable" : "Not Schedulable");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst[n], period[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &burst[i]);

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) scanf("%d", &period[i]);

    rate_monotonic_scheduling(n, burst, period);

    return 0;
}
/*
Enter the number of processes: 3
Enter the CPU burst times:
3 6 8
Enter the time periods:
3 4 5

Rate Monotonic Scheduling:
PID	Burst	Period
1	3	3
2	6	4
3	8	5

4.100000 <= 0.779763 => Not Schedulable



*/
