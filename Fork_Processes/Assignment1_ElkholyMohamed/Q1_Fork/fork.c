#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    int n = 4;
    for (i = 0; i < n; i++) {
        fork();
    }

    for (i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("hello\n");
    return 0;
}
