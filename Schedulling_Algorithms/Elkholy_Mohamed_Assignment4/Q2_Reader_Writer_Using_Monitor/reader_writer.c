#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t canRead = PTHREAD_COND_INITIALIZER;
pthread_cond_t canWrite = PTHREAD_COND_INITIALIZER;

int readerCount = 0;
int writerCount = 0;

void startread(int id) {
    pthread_mutex_lock(&mutex);
    while (writerCount > 0) {
        pthread_cond_wait(&canRead, &mutex);
    }
    readerCount++;
    printf("Reader %d starts reading\n", id);
    pthread_mutex_unlock(&mutex);
}

void endread(int id) {
    pthread_mutex_lock(&mutex);
    readerCount--;
    printf("Reader %d ends reading\n", id);
    if (readerCount == 0) {
        pthread_cond_signal(&canWrite);
    }
    pthread_mutex_unlock(&mutex);
}

void startwrite(int id) {
    pthread_mutex_lock(&mutex);
    while (readerCount > 0 || writerCount > 0) {
        pthread_cond_wait(&canWrite, &mutex);
    }
    writerCount++;
    printf("Writer %d starts writing\n", id);
    pthread_mutex_unlock(&mutex);
}

void endwrite(int id) {
    pthread_mutex_lock(&mutex);
    writerCount--;
    printf("Writer %d ends writing\n", id);
    pthread_cond_signal(&canWrite);
    pthread_cond_broadcast(&canRead);
    pthread_mutex_unlock(&mutex);
}

void *reader(void *arg) {
    int id = *((int *)arg);

    startread(id);
    // Reading operation
    sleep(1);
    endread(id);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);

    startwrite(id);
    // Writing operation
    sleep(1);
    endwrite(id);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != NUM_THREADS + 1) {
        printf("Usage: %s b1 b2 ... b10\n", argv[0]);
        return 1;
    }

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

    return 0;
}
