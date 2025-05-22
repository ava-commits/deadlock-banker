#include <stdio.h>
#include <stdbool.h>

#define P 5 
#define R 3 

int main() {
    int allocation[P][R], max[P][R], need[P][R];
    int available[R], work[R];
    bool finish[P] = {false};
    int safeSeq[P];


    printf("Enter Allocation matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources for A, B, C:\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

 
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

   
    for (int i = 0; i < R; i++) work[i] = available[i];

   
    printf("\n| Process |   Work (A B C)   | Allocation (A B C) |   Max (A B C)   |  Need (A B C)  |\n");
    printf("|---------|------------------|---------------------|------------------|----------------|\n");

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == R) {
                    printf("|   P%-3d |", i+1);
                    for (int k = 0; k < R; k++) printf(" %d", work[k]);
                    printf("             |");

                    for (int k = 0; k < R; k++) printf(" %d", allocation[i][k]);
                    printf("                |");

                    for (int k = 0; k < R; k++) printf(" %d", max[i][k]);
                    printf("             |");

                    for (int k = 0; k < R; k++) printf(" %d", need[i][k]);
                    printf("           |\n");

                  
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }

    printf("\nSafe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d", safeSeq[i] + 1);
        if (i != P - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}

OUTPUT :

Need Matrix:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

| Process |   Work (A B C)   | Allocation (A B C) |   Max (A B C)   |  Need (A B C)  |
|---------|------------------|---------------------|------------------|----------------|
|   P1   | 10 5 7             | 0 1 0                | 7 5 3             | 7 4 3           |
|   P2   | 10 6 7             | 2 0 0                | 3 2 2             | 1 2 2           |
|   P3   | 12 6 7             | 3 0 2                | 9 0 2             | 6 0 0           |
|   P4   | 15 6 9             | 2 1 1                | 2 2 2             | 0 1 1           |
|   P5   | 17 7 10             | 0 0 2                | 4 3 3             | 4 3 1           |

Safe sequence: P1 -> P2 -> P3 -> P4 -> P5
