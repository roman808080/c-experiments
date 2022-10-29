#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {

    int mypid = 1;
    wait(&mypid);
    printf("Success");
    exit(EXIT_SUCCESS);

    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (c_pid == 0) {
        printf("printed from child process %d\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);
        printf("printed from parent process %d\n", getpid());
    }

    exit(EXIT_SUCCESS);
}
