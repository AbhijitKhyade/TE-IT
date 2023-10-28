 printf("Total number of seek operations: %d\n", seekTime);

    float avgSeekTime = (float)seekTime / numRequests;
    printf("Average Seek Time is %.2f\n", avgSeekTime);