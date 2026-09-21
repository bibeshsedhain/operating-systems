/*
 * main3.c
 *
 * Creates two child processes. Each child runs for a random number
 * of iterations, sleeps for a random amount of time, and prints its
 * PID and parent PID. The parent waits for both children to finish.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    for (int i = 0; i < 2; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            srandom((unsigned int)getpid());

            int iterations = (random() % 30) + 1;

            for (int j = 0; j < iterations; j++)
            {
                printf("Child Pid: %d is going to sleep!\n", getpid());

                int sleep_time = (random() % 10) + 1;
                sleep(sleep_time);

                printf("Child Pid: %d is awake!\n", getpid());
                printf("Where is my Parent: %d?\n", getppid());
            }

            exit(0);
        }
    }

    int status;

    for (int i = 0; i < 2; i++)
    {
        pid_t completed_pid = wait(&status);

        if (completed_pid == -1)
        {
            perror("wait failed");
            exit(1);
        }

        printf("Child Pid: %d has completed\n", completed_pid);
    }

    return 0;
}