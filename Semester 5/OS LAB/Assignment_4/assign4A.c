#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define MAX_SIZE 5

int buffer[MAX_SIZE];
int in = 0;
int out = 0;
int producedCount = 0;
int consumedCount = 0;

sem_t mutex;    // Semaphore for mutual exclusion
sem_t empty;    // Semaphore to track empty slots in the buffer
sem_t full;     // Semaphore to track filled slots in the buffer

void *producer(void *args)
{
    int item = 1;

    while (producedCount < MAX_SIZE)
    {
        sem_wait(&empty);   // Wait if buffer is empty (no empty slots)
        sem_wait(&mutex);   // Gain exclusive access to the buffer

        buffer[in] = item;  // Place item in the buffer
        printf("Producer produced item %d\n", item);
        item++;
        in = (in + 1) % MAX_SIZE;  // Update the buffer index
        producedCount++;

        sem_post(&mutex);   // Release the mutex (buffer is no longer exclusive)
        sem_post(&full);    // Signal that buffer is no longer empty
    }

    pthread_exit(NULL);
}

void *consumer(void *args)
{
    while (consumedCount < MAX_SIZE)
    {
        sem_wait(&full);    // Wait if buffer is full (no filled slots)
        sem_wait(&mutex);   // Gain exclusive access to the buffer

        int item = buffer[out];  // Retrieve item from the buffer
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % MAX_SIZE;  // Update the buffer index
        consumedCount++;

        sem_post(&mutex);   // Release the mutex (buffer is no longer exclusive)
        sem_post(&empty);   // Signal that buffer is no longer full
    }

    pthread_exit(NULL);
}

int main()
{
    int numProducers, numConsumers;

    printf("Enter the number of producers: ");
    scanf("%d", &numProducers);

    printf("Enter the number of consumers: ");
    scanf("%d", &numConsumers);

    pthread_t producerThreads[numProducers];
    pthread_t consumerThreads[numConsumers];

    sem_init(&mutex, 0, 1);     // Initialize mutex to 1 (unlocked)
    sem_init(&full, 0, 0);      // Initialize full to 0 (no filled slots)
    sem_init(&empty, 0, MAX_SIZE); // Initialize empty to MAX_SIZE (all slots empty)

    for (int i = 0; i < numProducers; i++) {
        pthread_create(&producerThreads[i], NULL, producer, (void *)&i);
    }

    for (int i = 0; i < numConsumers; i++) {
        pthread_create(&consumerThreads[i], NULL, consumer, (void *)&i);
    }

    for (int i = 0; i < numProducers; i++) {
        pthread_join(producerThreads[i], NULL);
    }

    for (int i = 0; i < numConsumers; i++) {
        pthread_join(consumerThreads[i], NULL);
    }

    sem_destroy(&mutex);   // Cleanup the semaphores
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
