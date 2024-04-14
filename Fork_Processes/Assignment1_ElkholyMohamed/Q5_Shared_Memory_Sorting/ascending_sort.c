#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 2048
#define NUM_NUMBERS 10

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    int *shared_memory = (int *)mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    int numbers[NUM_NUMBERS];
    for (int i = 0; i < NUM_NUMBERS; i++) {
        numbers[i] = shared_memory[i];
    }

    for (int i = 0; i < NUM_NUMBERS - 1; i++) {
        for (int j = i + 1; j < NUM_NUMBERS; j++) {
            if (numbers[i] > numbers[j]) {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }

    printf("Sorted Numbers (ascending Order):\n");
    for (int i = 0; i < NUM_NUMBERS; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);

    shm_unlink(SHM_NAME);

    return 0;
}
