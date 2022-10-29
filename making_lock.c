#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include <pthread.h>

// https://stackoverflow.com/questions/10080811/what-happens-to-other-threads-when-one-thread-forks

pthread_t g_thread_1;
pthread_t g_thread_2;

pthread_mutex_t g_mut;

void *hell_function(void *arg)
{
    int i = *((int*) arg);

    printf("%i) PID = %d Trying to lock...\n", i, getpid());
    if (pthread_mutex_lock(&g_mut) != 0)
    {
        perror("mutex_lock failed to lock");
        exit(2);
    }


    printf("%i) PID = %d Before sleep.\n", i, getpid());
    sleep(1);
    printf("%i) PID = %d After sleep.\n", i, getpid());

    if (pthread_mutex_unlock(&g_mut) != 0)
    {
        perror("mutex_lock failed to unlock");
        exit(2);
    }

    return 0;
}

int main()
{
    ////////////////////////////////// create and an additional sleep
    if (pthread_mutex_init(&g_mut, NULL) != 0)
    {
        perror("mutex_lock failed to initialized");
        exit(1);
    }

    int first = 1;
    int createerror_1 = pthread_create(&g_thread_1, NULL, hell_function, &first);
    if (createerror_1 != 0)
    {
        return 2;
    }


    ////////////////////////////////// fork section
    pid_t c_pid = fork();

    if (c_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (c_pid == 0)
    {
        printf("printed from child process %d\n", getpid());
    }
    else
    {
        printf("printed from parent process %d\n", getpid());
    }
    ////////////////////////////////// fork section end

    int second = 2;
    int createerror_2 = pthread_create(&g_thread_2, NULL, hell_function, &second);
    if (createerror_2 != 0)
    {
        return 2;
    }

    pthread_join(g_thread_1, NULL); /*wait until the created thread terminates*/
    pthread_join(g_thread_2, NULL); /*wait until the created thread terminates*/

    if (c_pid != 0)
    {
        wait(NULL);
    }

    exit(EXIT_SUCCESS);
}
