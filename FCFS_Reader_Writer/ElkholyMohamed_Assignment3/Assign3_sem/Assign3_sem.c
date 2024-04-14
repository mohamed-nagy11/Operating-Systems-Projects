#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 10

sem_t mutex;
sem_t writeBlock;
sem_t readBlock;
int readerCount = 0;

void *reader(void *arg) {
    int id = *((int *)arg);

    sem_wait(&readBlock);
    sem_wait(&mutex);
    readerCount++;
    if (readerCount == 1) {
        sem_wait(&writeBlock);
    }
    sem_post(&mutex);
    sem_post(&readBlock);

    printf("Reader %d starts reading\n", id);
    // Reading operation
    sleep(1);
    printf("Reader %d ends reading\n", id);

    sem_wait(&mutex);
    readerCount--;
    if (readerCount == 0) {
        sem_post(&writeBlock);
    }
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);

    sem_wait(&readBlock);
    sem_wait(&writeBlock);

    printf("Writer %d starts writing\n", id);
    // Writing operation
    sleep(1);
    printf("Writer %d ends writing\n", id);

    sem_post(&writeBlock);
    sem_post(&readBlock);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != NUM_THREADS + 1) {
        printf("Usage: %s b1 b2 ... b10\n", argv[0]);
        return 1;
    }

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    sem_init(&readBlock, 0, 1);

    pthread_t threads[NUM_THREADS];
    int threadArgs[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threadArgs[i] = i + 1;
        if (atoi(argv[i + 1]) == 0) {
            pthread_create(&threads[i], NULL, reader, &threadArgs[i]);
        } else {
            pthread_create(&threads[i], NULL, writer, &threadArgs[i]);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    sem_destroy(&readBlock);

    return 0;
}
