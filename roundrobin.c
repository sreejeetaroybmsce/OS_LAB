#include <stdio.h>

int main() {
    int n, tq, current_time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int bt[20], rt[20], at[20], ct[20], tat[20], wt[20], p[20];

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
        p[i] = i + 1;
    }


    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                temp = at[j]; at[j] = at[j + 1]; at[j + 1] = temp;
                temp = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = temp;
                temp = rt[j]; rt[j] = rt[j + 1]; rt[j + 1] = temp;
                temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }
        }
    }

    while (completed < n) {
        int done_something = 0;
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] > 0) {
                done_something = 1;
                if (rt[i] > tq) {
                    current_time += tq;
                    rt[i] -= tq;
                } else {
                    current_time += rt[i];
                    rt[i] = 0;
                    completed++;

                    ct[i] = current_time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];


                    total_tat += tat[i];
                    total_wt += wt[i];
                }
            }
        }
        if (done_something == 0) {
            current_time++;
        }
    }

    printf("\nP#\tAT\tBT\tCT\tWT\tTAT");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", p[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }


    printf("\n\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
