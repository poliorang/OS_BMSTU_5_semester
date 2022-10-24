#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TIME_FOR_SLEEP 3

int main()
{
    pid_t children[2];
    int status;

    for (int i = 0; i < 2; i++)
    {
        if ((children[i] = fork()) == -1)
        {
            perror("Can't fork\n");
            exit(EXIT_FAILURE);
        }
        else if (children[i] == 0)
        {
            printf("\nChild %d: PID = %d, PPID = %d, PGRP = %d\n", i + 1, getpid(), getppid(), getpgrp());
        }
        else
        {
           // printf("Parent: PID = %d, PGRP = %d, CHILD = %d\n", getpid(), getpgrp(), children[i]);
            children[i] = waitpid(children[i], &status, WCONTINUED);

            if (children[i] == -1)
            {
                perror("Can't wait\n");
                exit(EXIT_FAILURE);
            }

            printf("Child %d finished, status: %d\n", children[i], status);

            if (WIFEXITED(status))
                printf("Child finished, code: %d\n", WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                printf("Child finished, signal %d\n", WTERMSIG(status));
            else if (WIFSTOPPED(status))
                printf("Child stopped, signal %d\n", WSTOPSIG(status));
        }
    }

    return EXIT_SUCCESS;
}