#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUM_PROCESSES 10
#define SHARED_MEM_NAME "/reader_writer_shared_mem"

// Define the structure to store shared variables
struct SharedVariables {
    sem_t mutex;
    sem_t writeBlock;
    sem_t readBlock;
    int readerCount;
};

void child_reader(int id, struct SharedVariables *shared_vars) {
    sem_wait(&shared_vars->readBlock);
    sem_wait(&shared_vars->mutex);
    shared_vars->readerCount++;
    if (shared_vars->readerCount == 1) {
        sem_wait(&shared_vars->writeBlock);
    }
    sem_post(&shared_vars->mutex);
    sem_post(&shared_vars->readBlock);

    printf("Reader %d starts reading\n", id);
    // Reading operation
    sleep(1);
    printf("Reader %d ends reading\n", id);

    sem_wait(&shared_vars->mutex);
    shared_vars->readerCount--;
    if (shared_vars->readerCount == 0) {
        sem_post(&shared_vars->writeBlock);
    }
    sem_post(&shared_vars->mutex);

    exit(EXIT_SUCCESS);
}

void child_writer(int id, struct SharedVariables *shared_vars) {
    sem_wait(&shared_vars->readBlock);
    sem_wait(&shared_vars->writeBlock);

    printf("Writer %d starts writing\n", id);
    // Writing operation
    sleep(1);
    printf("Writer %d ends writing\n", id);

    sem_post(&shared_vars->writeBlock);
    sem_post(&shared_vars->readBlock);

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != NUM_PROCESSES + 1) {
        printf("Usage: %s b1 b2 ... b10\n", argv[0]);
        return 1;
    }

    // Create shared memory
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set the size of shared memory
    if (ftruncate(shm_fd, sizeof(struct SharedVariables)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map shared memory
    struct SharedVariables *shared_vars = (struct SharedVariables *)mmap(NULL, sizeof(struct SharedVariables), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_vars == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores and variables in shared memory
    sem_init(&shared_vars->mutex, 1, 1);
    sem_init(&shared_vars->writeBlock, 1, 1);
    sem_init(&shared_vars->readBlock, 1, 1);
    shared_vars->readerCount = 0;

    // Close shared memory
    if (close(shm_fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    pid_t processIds[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (atoi(argv[i + 1]) == 0) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process for reader
                child_reader(i + 1, shared_vars);
            } else {
                processIds[i] = pid;
            }
        } else {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process for writer
                child_writer(i + 1, shared_vars);
            } else {
                processIds[i] = pid;
            }
        }
    }

    // Wait for all child processes to complete
    int status;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        waitpid(processIds[i], &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            printf("Child process %d terminated abnormally\n", processIds[i]);
        }
    }

    // Unmap shared memory
    if (munmap(shared_vars, sizeof(struct SharedVariables)) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Remove shared memory
    if (shm_unlink(SHARED_MEM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
