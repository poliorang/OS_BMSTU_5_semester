#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 2

int main()
{
    int child[N];

    printf("Parent process start. PID: %d, GROUP: %d\n", getpid(), getpgrp());

    for (int i = 0; i < N; i++)
    {
        int child_pid = fork();

        if (child_pid == -1)
        {
            perror("Can\'t fork()\n");
            exit(EXIT_FAILURE);
        }
        else if (!child_pid)
        {
            printf("\nChild %d | PID: %d, PPID: %d, GROUP: %d [before sleep]\n", i + 1, getpid(), getppid(), getpgrp());
            sleep(2);
            printf("Child %d | PID: %d, PPID: %d, GROUP: %d [after sleep]\n", i + 1, getpid(), getppid(), getpgrp());

            return EXIT_SUCCESS;
        }
        else
        {
            child[i] = child_pid;
        }
    }

//    sleep(1);
    printf("Parent process finished. Children: %d, %d \nParent: PID: %d, GROUP: %d\n", child[0], child[1], getpid(), getpgrp());

    return EXIT_SUCCESS;
}

