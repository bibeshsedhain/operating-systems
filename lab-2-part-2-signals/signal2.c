#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t signal_received = 0;

void handler(int sig)
{
    (void)sig;

    printf("Hello World!\n");

    signal_received = 1;

    alarm(5);
}

int main()
{
    signal(SIGALRM, handler);

    alarm(5);

    while (1)
    {
        pause();

        if (signal_received)
        {
            printf("Turing was right!\n");

            signal_received = 0;
        }
    }

    return 0;
}