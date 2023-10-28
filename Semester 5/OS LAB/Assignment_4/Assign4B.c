#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include<unistd.h>

sem_t mutex;          // To protect the shared resources
sem_t writeSemaphore; // semaphore for writer
int readerNum = 0;    // number of current readers

void *reader(void *arg)
{
    while (1)
    {
        // Reader wants to enter the critical section
        sem_wait(&mutex);
        readerNum++;
        if (readerNum == 1)
        {
            sem_wait(&writeSemaphore); // first reader blocks writer
        }
        sem_post(&mutex);

        // Reading the shared resource
        printf("Reader %ld is reading ...\n", (long)arg);
        // Simulate reading by sleeping for a random time
        usleep(rand() % 1000000);

        // Reader is living the critical section
        sem_wait(&mutex);
        readerNum--;
        if (readerNum == 0)
        {
            sem_post(&writeSemaphore); // Last reader unblocks the reader
        }
        sem_post(&mutex);

        // Perform some other non-critical work
        usleep(rand() % 1000000);
    }
}

void *writer(void *arg)
{
    while (1)
    {
        // Writer wants to enter the critical section
        sem_wait(&writeSemaphore);

        // Writing to the shared resource
        printf("Writer %ld is writing...\n", (long)arg);

        // Simulate writing by sleeping for a random time
        usleep(rand() % 1000000);

        // Writer is leaving the critical section
        sem_post(&writeSemaphore);

        // Perform some other non-critical work
        usleep(rand() % 1000000);
    }
}

int main()
{
    int readers_no, writers_no;
    printf("\nEnter the number of readers: ");
    scanf("%d", &readers_no);

    printf("\nEnter the number of writers: ");
    scanf("%d", &writers_no);

    pthread_t readers[readers_no];
    pthread_t writers[writers_no];

    // Initialize Semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeSemaphore, 0, 1);

    // Create Reader threads
    for (long i = 0; i < readers_no; i++)
    {
        pthread_create(&readers[i], NULL, reader, (void *)i);
    }

    // Create Writer threads
    for (long i = 0; i < writers_no; i++)
    {
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    // Join threads
    for (int i = 0; i < readers_no; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < writers_no; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // clean up the semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeSemaphore);

    return 0;
}