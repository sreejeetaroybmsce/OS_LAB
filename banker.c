#include <stdio.h>

int main() {
    int n, r, i, j, k;

    printf("Enter no. of processes: ");
    scanf("%d", &n);

    printf("Enter no. of resources: ");
    scanf("%d", &r);

    int alloc[n][r], max[n][r], need[n][r];
    int avail[r], finish[n], safe[n];

    // Input Allocation and Max
    for(i = 0; i < n; i++) {
        printf("\nP%d Allocation: ", i);
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

        printf("P%d Max: ", i);
        for(j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nEnter Available Resources: ");
    for(i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    // ---------- BANKER'S ALGORITHM ----------
    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(!finish[i]) {

                for(j = 0; j < r; j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == r) {
                    for(k = 0; k < r; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found)
            break;
    }

    // Output for Banker's Algorithm
    if(count == n) {
        printf("\nSYSTEM IS IN SAFE STATE");
        printf("\nSafe Sequence: ");

        for(i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    }
    else
        printf("\nSYSTEM IS NOT SAFE");

    // ---------- DEADLOCK DETECTION ----------
    int deadlock = 0;

    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            deadlock = 1;
            printf("\nProcess P%d is in Deadlock", i);
        }
    }

    if(deadlock == 0)
        {printf("\n\nNO DEADLOCK DETECTED");

        }

    return 0;
}
