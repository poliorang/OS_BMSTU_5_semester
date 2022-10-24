#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define N 2

int main()
{
    setbuf(stdout, NULL);
    int child[N];
    char *com[N] = {"./task03_01", "./task03_02"};

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
            printf("Child %d | PID: %d, PPID: %d, GROUP: %d\n", i + 1, getpid(), getppid(), getpgrp());
            int rc = execl(com[i], com[i], NULL);

            if (rc == -1)
            {
                perror("Can't exec");
                exit(EXIT_FAILURE);
            }
            return EXIT_SUCCESS;
        }
        else
        {
            child[i] = child_pid;
        }
    }

    for (int i = 0; i < N; i++)
    {
        int status;
        int statval = 0;

        pid_t child_pid = wait(&status);

        printf("Child process %d finished. Status: %d\n", child_pid, status);

        if (WIFEXITED(statval))
        {
            printf("Child process %d finished. Code: %d\n", i + 1, WEXITSTATUS(statval));
        }
        else if (WIFSIGNALED(statval))
        {
            printf("Child process %d finished from signal with code: %d\n", i + 1, WTERMSIG(statval));
        }
        else if (WIFSTOPPED(statval))
        {
            printf("Child process %d finished stopped. Number signal: %d\n", i + 1, WSTOPSIG(statval));
        }
    }

    printf("Parent process finished. Children: %d, %d \nParent: PID: %d, GROUP: %d\n ", child[0], child[1], getpid(), getpgrp());

    return EXIT_SUCCESS;
}
