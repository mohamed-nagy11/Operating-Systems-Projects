#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    int pipe1[2], pipe2[2];
    
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid_t child1 = fork();
    
    if (child1 == -1) {
        perror("Forking child 1 failed");
        exit(1);
    }

    if (child1 == 0) {
        close(pipe1[0]);

        time_t now;
        struct tm *local_time;
        char date[11];

        time(&now);
        local_time = localtime(&now);
        strftime(date, sizeof(date), "%m/%d/%Y", local_time);

        printf("Child 1: Date in MM/DD/YYYY format: %s\n", date);

        write(pipe1[1], date, sizeof(date));
        close(pipe1[1]);

        exit(0);
    }

    pid_t child2 = fork();
    
    if (child2 == -1) {
        perror("Forking child 2 failed");
        exit(1);
    }

    if (child2 == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        char date[11];

        read(pipe1[0], date, sizeof(date));
        close(pipe1[0]);

        struct tm tm;
        strptime(date, "%m/%d/%Y", &tm);
        strftime(date, sizeof(date), "%d/%m/%y", &tm);

        printf("Child 2: Date in DD/MM/YY format: %s\n", date);

        write(pipe2[1], date, sizeof(date));
        close(pipe2[1]);

        exit(0);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);

    char formatted_date[11];

    read(pipe2[0], formatted_date, sizeof(formatted_date));
    close(pipe2[0]);

    printf("Parent: Date in DD/MM/YY format: %s\n", formatted_date);

    wait(NULL);
    wait(NULL);

    return 0;
}