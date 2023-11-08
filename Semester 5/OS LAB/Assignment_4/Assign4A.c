#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count=0,numProducers, numConsumers;
sem_t empty, full, mutex;

void *producer(void *arg){
    int producer_id = *((int *)arg);
    int item;
    while(1){
        int item = rand() % 100;

        if(count == BUFFER_SIZE){
            printf("\n\nBUFFER is FULL...");
            sleep(1);
        }

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[count++] = item;
        printf("\n\nProducer %d produced an item %d", producer_id, item);
        
        printf("\nBuffer Size: %d", count);

        //print buffer
        printf("\nBuffer: ");
        for(int i=0;i<count;i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg){
    int consumer_id = *((int *)arg);
    int item;
    while(1){
        int item = rand() % 100;

        if(count == 0){
            printf("\n\nBUFFER is EMPTY...");
            sleep(2);
        }

        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[--count]; 
        printf("\n\nConsumer %d consumed an item %d", consumer_id, item);
        printf("\nBuffer Size: %d", count);

        //print buffer
        printf("\nBuffer: ");
        for(int i=0;i<count;i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");

        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(){
    printf("Enter the no of producers and consumers: ");
    scanf("%d %d",&numProducers, &numConsumers);

    //create threads
    pthread_t producer_thread[numProducers];
    pthread_t consumer_thread[numConsumers];

    //Initialization of semaphore
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    //producer and consumer id's
    int producer_ids[numProducers];
    int consumer_ids[numConsumers];

    //pthread create for producers
    for(int i=0;i<numProducers;i++){
        producer_ids[i] = i+1;
        pthread_create(&producer_thread[i], NULL, producer, &producer_ids[i]);
    }

    //pthread create for consumers
    for(int i=0;i<numConsumers;i++){
        consumer_ids[i] = i+1;
        pthread_create(&consumer_thread[i], NULL, consumer, &consumer_ids[i]);
    }

    //pthread join for producers
    for(int i=0;i<numProducers;i++){
        pthread_join(producer_thread[i], NULL);
    }

    //pthread join for consumers
    for(int i=0;i<numConsumers;i++){
        pthread_join(consumer_thread[i], NULL);
    }

    //destroy the semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}