#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int remaining_need[100][100], allocation[100][100], maximumDemands[100][100], availableResources[100];
bool isProcessFinished[100];
int safeSequence[100];

void isSystemSafe(int numProcesses, int numResources) {
    int i, j, work[100], count = 0;
    for (i = 0; i < numResources; i++)
        work[i] = availableResources[i];

    for (i = 0; i < 100; i++)
        isProcessFinished[i] = false;

    while (count < numProcesses) {
        bool canAllocate = false;

        for (i = 0; i < numProcesses; i++) {
            if (isProcessFinished[i] == false) {
                for (j = 0; j < numResources; j++) {
                    if (work[j] < remaining_need[i][j]) {
                        break;
                    }
                }
                if (j == numResources) {
                    for (j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    isProcessFinished[i] = true;
                    canAllocate = true;
                }
            }
        }

        if (canAllocate == false) {
            printf("System Is not safe\n");
            return;
        }
    }

    printf("System is in a safe state\n");
    printf("Safe sequence: ");
    for (i = 0; i < numProcesses; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
}

int main() {
    int i, j, numProcesses, numResources;
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &numProcesses, &numResources);

    printf("Enter the available resources:\n");
    for (i = 0; i < numResources; i++) {
        scanf("%d", &availableResources[i]);
    }

    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < numProcesses; i++)
        for (j = 0; j < numResources; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter the matrix for maximum demand of each process:\n");
    for (i = 0; i < numProcesses; i++)
        for (j = 0; j < numResources; j++)
            scanf("%d", &maximumDemands[i][j]);

    // Calculation of the remaining_need matrix
    for (i = 0; i < numProcesses; i++)
        for (j = 0; j < numResources; j++)
            remaining_need[i][j] = maximumDemands[i][j] - allocation[i][j];

    isSystemSafe(numProcesses, numResources);

    int processIndex, resourceRequest[100];
    printf("Enter the process number for resource request: ");
    scanf("%d", &processIndex);

    printf("Enter the requested instances of Each: ");
    for (i = 0; i < numResources; i++)
        scanf("%d", &resourceRequest[i]);

    for (i = 0; i < numResources; i++) {
        if (remaining_need[processIndex][i] < resourceRequest[i] || resourceRequest[i] > availableResources[i]) {
            printf("Cannot request\n");
            break;
        }
    }

    if (i == numResources) {
        for (i = 0; i < numResources; i++) {
            allocation[processIndex][i] += resourceRequest[i];
            availableResources[i] -= resourceRequest[i];
            remaining_need[processIndex][i] -= resourceRequest[i];
        }
        isSystemSafe(numProcesses, numResources);
    }
    return 0;
}
