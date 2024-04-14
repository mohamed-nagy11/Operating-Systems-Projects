#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 2048
#define NUM_NUMBERS 10

int main()
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(1);
    }

    ftruncate(shm_fd, SHM_SIZE);

    int *shared_memory = (int *)mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < NUM_NUMBERS; i++)
    {
        shared_memory[i] = rand() % 1000 + 1;
    }

    munmap(shared_memory, SHM_SIZE);
    close(shm_fd);

    return 0;
}
