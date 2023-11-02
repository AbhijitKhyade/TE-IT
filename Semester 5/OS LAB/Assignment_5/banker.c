#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int remaining_need[100][100], allocation[100][100], maximumDemands[100][100], availableResources[100];
bool isProcessFinished[100];
int safeSequence[100];

void isSystemSafe(int numProcesses, int numResources) {
    int i, j, work[100], count = 0;
    //copy all available resources in work matrix
    for (i = 0; i < numResources; i++)
        work[i] = availableResources[i];

    //Initialize the ProcessFinished array
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

void needMatrix(int numProcesses, int numResources){
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            remaining_need[i][j] = maximumDemands[i][j] - allocation[i][j];
}

int main() {
    int i, j, numProcesses, numResources;
    int processIndex, resourceRequest[100];
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
    needMatrix(numProcesses, numResources);

    while(1){
        printf("1) Calculate Need Matrix\n");
        printf("2) Check safety\n");
        printf("3) Request Resource\n");
        printf("4) Exit\n");
        printf("Enter your choice:");
        int choice;
        scanf("%d",&choice);

        if(choice == 4){
            printf("\nExited from program...\n");
            break;
        }

        switch (choice){
        case 1:
            needMatrix(numProcesses, numResources);
            break;
        case 2:
            isSystemSafe(numProcesses, numResources);
            break;
        case 3:
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
            break;
        default:
            printf("\nInValid Choice, Try again...");
            break;
        }
    }
    return 0;
}
