#include <stdio.h>
#include <stdlib.h>

int main() {
    int numRequests, headPosition, maxRange, seekTime = 0;

    printf("Enter the maximum range of the disk: ");
    scanf("%d", &maxRange);

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    printf("Enter the initial head position: ");
    scanf("%d", &headPosition);

    int requests[numRequests];

    printf("Enter the requests: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Sort the requests
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests-1-i; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }

    // Find the first request greater than or equal to head position
    int startIndex = 0;
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] > headPosition) {
            startIndex = i;
            break;
        }
    }

    // Print the initial head position
    printf("Seek Sequence: %d", headPosition);

    // Calculate seek time for the right side
    for (int i = startIndex; i < numRequests; i++) {
        seekTime += abs(requests[i] - headPosition);
        headPosition = requests[i];
        printf(" -> %d", headPosition);  // Print the request being serviced
    }
    seekTime += abs(maxRange - headPosition);
    headPosition = maxRange;
    printf(" -> %d", headPosition);

    // Calculate seek time for the left side
    for (int i = startIndex - 1; i >= 0; i--) {
        seekTime += abs(requests[i] - headPosition);
        headPosition = requests[i];
        printf(" -> %d", headPosition);  // Print the request being serviced
    }

    printf("\nTotal number of seek operations: %d\n", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("Average Seek Time is %.2f\n", avgSeekTime);

    return 0;
}
