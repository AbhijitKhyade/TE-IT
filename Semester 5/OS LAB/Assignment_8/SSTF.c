#include <stdio.h>
#include <stdlib.h>

int calculateTotalSeekTime(int requestQueue[], int numRequests, int initialHead) {
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
    printf("Seek Sequence: %d", initialHead);
    for (int i = 0; i < numRequests; i++) {
        if (seekSequence[i] != -1) {
            printf(" -> %d", seekSequence[i]);
        }
    }
    printf("\n");

    return seekTime;
}

int main() {
    int numRequests, initialHead;

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    int requestQueue[numRequests];

    printf("Enter the request queue: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    int totalSeekTime = calculateTotalSeekTime(requestQueue, numRequests, initialHead);
    float avgSeekTime = (float)totalSeekTime / numRequests;

    printf("Total seek time: %d\n", totalSeekTime);
    printf("Average seek time: %.2f\n", avgSeekTime);

    return 0;
}
