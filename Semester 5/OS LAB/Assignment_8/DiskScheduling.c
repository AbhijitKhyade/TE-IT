#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate total seek time for FCFS
int calculateTotalSeekTimeFCFS(int requestQueue[], int numRequests, int initialHead) {
    int seekTime = 0;
    printf("\nSeek Sequence: %d", initialHead); // Print the initial head position
    for (int i = 0; i < numRequests; i++) {
        int seek = abs(initialHead - requestQueue[i]);
        seekTime += seek;
        printf(" -> %d", requestQueue[i]); // Print the request being serviced
        initialHead = requestQueue[i];
    }
    printf("\nTotal number of seek operations: %d", seekTime);
    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}
// Function to calculate total seek time for SSTF
int calculateTotalSeekTimeSSTF(int requestQueue[], int numRequests, int initialHead){
    int seekTime = 0;
    int currentPosition = initialHead;

    // Create an array to keep track of visited requests
    int visited[numRequests];
    for (int i = 0; i < numRequests; i++) {
        visited[i] = 0;
    }

    // Create an array to store the seek sequence
    int seekSequence[numRequests];
    for (int i = 0; i < numRequests; i++) {
        seekSequence[i] = -1;
    }
    
    for (int i = 0; i < numRequests; i++) {
        int shortestSeek = 999999;
        int nextRequest;

        // Find the request with the shortest seek time from the current position
        for (int j = 0; j < numRequests; j++) {
            if (!visited[j]) {
                int seek = abs(currentPosition - requestQueue[j]);
                if (seek < shortestSeek) {
                    shortestSeek = seek;
                    nextRequest = j;
                }
            }
        }

        // Update the seek time, mark the request as visited, and add it to the sequence
        seekTime += shortestSeek;
        visited[nextRequest] = 1;
        currentPosition = requestQueue[nextRequest];
        seekSequence[i] = requestQueue[nextRequest];
    }

    // Print the seek sequence
    printf("\nSeek Sequence: %d", initialHead);
    for (int i = 0; i < numRequests; i++) {
        if (seekSequence[i] != -1) {
            printf(" -> %d", seekSequence[i]);
        }
    }
    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}
// Function to calculate total seek time for LOOK
int calculateTotalSeekTimeLook(int requestQueue[], int numRequests, int initialHead, int maxRange, int minRange){
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){ //Left direction
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}
// Function to calculate total seek time for C-LOOK
int calculateTotalSeekTimeC_Look(int requestQueue[], int numRequests, int initialHead, int maxRange, int minRange){
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){ //Left direction
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(requestQueue[numRequests-1] - headPosition);
        headPosition = requestQueue[numRequests-1];
        printf(" -> %d", headPosition);
        for (int i = numRequests-2; i>=startIndex; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(requestQueue[0] - headPosition);
        headPosition = requestQueue[0];
        printf(" -> %d", headPosition);
        for (int i = 1; i <=startIndex-1; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}
// Function to calculate total seek time for SCAN
int calculateTotalSeekTimeSCAN(int requestQueue[], int numRequests, int initialHead, int maxRange, int minRange) {
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){ //Left direction
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(minRange - headPosition);
        headPosition = minRange;
        printf(" -> %d", headPosition);
        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(maxRange - headPosition);
        headPosition = maxRange;
        printf(" -> %d", headPosition);
        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}
// Function to calculate total seek time for C-SCAN
int calculateTotalSeekTimeC_SCAN(int requestQueue[], int numRequests, int initialHead, int maxRange, int minRange){
    int seekTime = 0;
    int headPosition = initialHead;
    int startIndex = 0;

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - 1 - i; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }
    //find the greater index
    for (int i = 0; i < numRequests; i++) {
        if (requestQueue[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    //decide the direction
    int seekRight = abs(requestQueue[startIndex] - headPosition);
    int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
    printf("\nSeekRight: %d", seekRight);
    printf("\nSeekLeft: %d", seekLeft);

    int direction;
    printf("\n1.Left Direction(Lower values)");
    printf("\n2.Right Direction(Greater values)");
    printf("\nChoose the direction: ");
    scanf("%d", &direction);
    if(direction == 1){
        printf("\nSeek time towards left is minimum so moving towards left...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex - 1; i >= 0; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(minRange - headPosition);
        headPosition = minRange;
        printf(" -> %d", headPosition);
        seekTime += abs(maxRange - headPosition);
        headPosition = maxRange;
        printf(" -> %d", headPosition);
        for (int i = numRequests-1; i >= startIndex; i--) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }
    else if(direction == 2){
        printf("\nSeek time towards right is minimum or equal so moving towards right...");
        printf("\n----------------------------------------------------------------------");
        printf("\nSeek Sequence: %d", headPosition);

        for (int i = startIndex; i < numRequests; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
        seekTime += abs(maxRange - headPosition);
        headPosition = maxRange;
        printf(" -> %d", headPosition);
        seekTime += abs(minRange - headPosition);
        headPosition = minRange;
        printf(" -> %d", headPosition);
        for (int i = 0; i <=startIndex-1; i++) {
            seekTime += abs(requestQueue[i] - headPosition);
            headPosition = requestQueue[i];
            printf(" -> %d", headPosition);
        }
    }

    printf("\nTotal number of seek operations: %d", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("\nAverage Seek Time is %.2f\n", avgSeekTime);
    printf("\n");
    return seekTime;
}

int main() {
    int choice, numRequests, initialHead, maxRange, minRange, seekTime = 0;
    printf("Enter the maximum range of the disk: ");
    scanf("%d", &maxRange);
    printf("Enter the minimum range of the disk: ");
    scanf("%d", &minRange);

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);
    int requestQueue[numRequests];

    printf("Enter the requests: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    while(1){
        printf("-----Disk Scheduling Algorithms-----\n");
        printf("------------------------------------\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. LOOk\n");
        printf("6. C-LOOK\n");
        printf("7. Exit\n");
        printf("Choose the Disk scheduling Algorithm: ");
        scanf("%d", &choice);

        if(choice == 7){
            printf("\nExited from program...");
            break;
        }

        switch (choice){
            case 1:
                printf("\n-------------------------FCFS------------------------");
                printf("\n-----------------------------------------------------");
                seekTime = calculateTotalSeekTimeFCFS(requestQueue, numRequests, initialHead);
                break;
            case 2:
                printf("\n-------------------------SSTF------------------------");
                printf("\n-----------------------------------------------------");
                seekTime = calculateTotalSeekTimeSSTF(requestQueue, numRequests, initialHead);
                break;
            case 3:
                printf("\n-------------------------SCAN------------------------");
                printf("\n-----------------------------------------------------");
                seekTime = calculateTotalSeekTimeSCAN(requestQueue, numRequests, initialHead, maxRange, minRange);
                break;
            case 4:
                printf("\n-------------------------C-SCAN----------------------");
                printf("\n-----------------------------------------------------");
                seekTime = calculateTotalSeekTimeC_SCAN(requestQueue, numRequests, initialHead,maxRange,minRange);
                break;
            case 5:
                printf("\n-------------------------LOOK------------------------");
                printf("\n-----------------------------------------------------");
                seekTime = calculateTotalSeekTimeLook(requestQueue, numRequests,initialHead,maxRange, minRange);
                break;
            case 6:
                printf("\n-------------------------C-LOOK----------------------");
                printf("\n-----------------------------------------------------");
                seekTime = calculateTotalSeekTimeC_Look(requestQueue,numRequests, initialHead,maxRange,minRange);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                continue;
        } 
    }
    return 0;
}
