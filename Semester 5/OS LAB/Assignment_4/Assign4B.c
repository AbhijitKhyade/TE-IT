#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// void *writer_thr(void *temp);
// void *reader_thr(void *temp);
sem_t mutex;
sem_t writeSemaphore;
int readcount = 0, w, r, writer_count = 0;

void *writer_thr(void *temp) {
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);

    printf("Writer %d is waiting for writing...\n", id);

    // Check if writeSemaphore is locked by readers
    int sem_val;
    sem_getvalue(&writeSemaphore, &sem_val);
    if (sem_val == 0) {
        printf("writeSemaphore is locked by readers.\n");
    } else {
        printf("writeSemaphore is unlocked.\n");
    }

    sem_wait(&writeSemaphore);
    printf("Writer %d is writing...\n", id);
    sleep(2);
    sem_post(&writeSemaphore);
    printf("Writer %d leaving the critical section.\n", id);
    // Increment the writer count
    writer_count++;
    pthread_exit(NULL);
}

void *reader_thr(void *temp) {
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);

    printf("Reader %d wants to read the shared resource/data.\n", id);

    sem_wait(&mutex);
    readcount++;
    if (readcount == 1) {
        printf("This is the first reader; writeSemaphore is locked.\n");
        sem_wait(&writeSemaphore);
    }
    sem_post(&mutex);

    printf("Reader %d is reading.\n", id);
    printf("Reader %d leaving.\n", id);
    sleep(3);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0) {
        printf("This is the last reader writeSemaphore is unlocked.\n");
        sem_post(&writeSemaphore);
    }
    sem_post(&mutex);

    pthread_exit(NULL);
}

int main() {
    int i;

    printf("\nEnter number of readers: ");
    scanf("%d", &r);
    printf("\nEnter number of writers: ");
    scanf("%d", &w);

    //Initialization of Semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeSemaphore, 0, 1);

    //creation of threads
    pthread_t reader[r]; 
    pthread_t writer[w];

    //pthread create for readers
    for (i = 1; i <= r; i++) {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&reader[i], NULL, reader_thr, (void *)reader_id);
    }

    //pthread create for writers
    for (i = 1; i <= w; i++) {
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writer[i], NULL, writer_thr, (void *)writer_id);
    }

    //pthread join for readers
    for (i = 1; i <= r; i++) {
        pthread_join(reader[i], NULL);
    }

    //pthread join for writers
    for (i = 1; i <= w; i++) {
        pthread_join(writer[i], NULL);
    }

    //destroy the semaphores
    sem_destroy(&writeSemaphore);
    sem_destroy(&mutex);

    printf("Total Writers: %d\n", writer_count);
    pthread_exit(NULL);
    return 0;
}