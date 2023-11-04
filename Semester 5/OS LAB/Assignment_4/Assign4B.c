#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *writer_thr(void *temp);
void *reader_thr(void *temp);
sem_t mutex;
sem_t writeSemaphore;
int readcount = 0, w, r;

void *writer_thr(void *temp) {
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);

    printf("\nWriter %d is trying to enter the database for modifying data.", id);
    sem_wait(&writeSemaphore);
    printf("\nWriter %d is writing in the database.", id);
    sleep(3);
    printf("\nWriter %d is leaving the database.\n", id);
    sem_post(&writeSemaphore);
    pthread_exit(NULL);
}

void *reader_thr(void *temp) {
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);

    printf("\nReader %d is trying to enter the database for reading.", id);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&writeSemaphore);
    sem_post(&mutex);

    printf("\nReader %d is now reading in the database.", id);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&writeSemaphore);
    sem_post(&mutex);

    printf("\nReader %d has left the database.\n", id);
    sleep(3);
    pthread_exit(NULL);
}

int main() {
    long int i;
    sem_init(&mutex, 0, 1);
    sem_init(&writeSemaphore, 0, 1);
    pthread_t reader[100], writer[100];

    printf("\nEnter number of readers: ");
    scanf("%d", &r);
    printf("\nEnter number of writers: ");
    scanf("%d", &w);

    for (i = 1; i <= w; i++) {
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writer[i], NULL, writer_thr, (void *)writer_id);
    }

    for (i = 1; i <= r; i++) {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&reader[i], NULL, reader_thr, (void *)reader_id);
    }

    for (i = 1; i <= w; i++) {
        pthread_join(writer[i], NULL);
    }

    for (i = 1; i <= r; i++) {
        pthread_join(reader[i], NULL);
    }

    sem_destroy(&writeSemaphore);
    sem_destroy(&mutex);

    pthread_exit(NULL); // Exit the main thread gracefully
}