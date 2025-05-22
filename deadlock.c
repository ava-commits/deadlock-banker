#include <stdio.h>
#include <stdbool.h>

#define P 5 
#define R 3 

int main() {
    int allocation[P][R], request[P][R], available[R], work[R];
    bool finish[P] = {false};

    printf("Enter Allocation matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);


    printf("Enter Request matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &request[i][j]);


    printf("Enter Available resources (A B C):\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < R; i++)
        work[i] = available[i];


    printf("\n| Process |   Work (A B C)   | Allocation (A B C) | Request (A B C) |\n");
    printf("|---------|------------------|---------------------|------------------|\n");

    bool deadlock = false;
    int executed = 0;

    while (executed < P) {
        bool progress = false;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (request[i][j] > work[j])
                        break;
                }

                if (j == R) {
                    printf("|   P%-3d |", i + 1);
                    for (int k = 0; k < R; k++) printf(" %d", work[k]);
                    printf("             |");

                    for (int k = 0; k < R; k++) printf(" %d", allocation[i][k]);
                    printf("                |");

                    for (int k = 0; k < R; k++) printf(" %d", request[i][k]);
                    printf("             |\n");

                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    finish[i] = true;
                    progress = true;
                    executed++;
                }
            }
        }

        if (!progress)
            break; 
    }
    bool foundDeadlock = false;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            foundDeadlock = true;
            break;
        }
    }

    if (foundDeadlock) {
        printf("\nSystem is in a deadlock state.\nDeadlocked processes: ");
        for (int i = 0; i < P; i++) {
            if (!finish[i])
                printf("P%d ", i + 1);
        }
        printf("\n");
    } else {
        printf("\nSystem is not in a deadlock state.\n");
    }

    return 0;
}

OUTPUT:

Enter Allocation matrix (5 x 3):
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
Enter Request matrix (5 x 3):
0 0 0
2 0 2
0 0 1
1 0 0
0 0 2
Enter Available resources (A B C):
0 1 0

| Process |   Work (A B C)   | Allocation (A B C) | Request (A B C) |
|---------|------------------|---------------------|------------------|
|   P1   | 0 1 0             | 0 1 0                | 0 0 0             |

System is in a deadlock state.