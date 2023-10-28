#include <stdio.h>
#include <math.h>

int calculateTotalSeekTimeFCFS(int requestQueue[], int numRequests, int initialHead){
    int totalSeek = 0;

    printf("Seek Sequence: %d", initialHead); // Print the initial head position

    for (int i = 0; i < numRequests; i++){
        int seek = abs(initialHead - requestQueue[i]);
        totalSeek += seek;
        printf(" -> %d", requestQueue[i]); // Print the request being serviced
        initialHead = requestQueue[i];
    }
    printf("\n"); // Print a new line to separate the seek sequence
    return totalSeek;
}

int main()
{
    int numRequests, initialHead, i;
    float avgSeekTime = 0;

    printf("-----FCFS Disk Scheduling Algorithm-----\n");
    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);
    int requestQueue[numRequests];

    printf("Enter the requests: ");
    for (i = 0; i < numRequests; i++){
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    int totalSeek = calculateTotalSeekTimeFCFS(requestQueue, numRequests, initialHead);
    avgSeekTime = (float)totalSeek / numRequests;

    printf("Total number of seek operations: %d\n", totalSeek);
    printf("Average Seek Time is %f\n", avgSeekTime);

    return 0;
}
