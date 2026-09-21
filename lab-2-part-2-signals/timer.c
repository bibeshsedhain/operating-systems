#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarm_count = 0;
volatile sig_atomic_t signal_received = 0;

time_t start_time;

void alarm_handler(int sig)
{
    (void)sig;

    alarm_count++;

    printf("Hello World!\n");

    signal_received = 1;

    alarm(1);
}

void interrupt_handler(int sig)
{
    (void)sig;

    time_t end_time = time(NULL);

    printf("\nProgram exiting...\n");

    printf("Number of alarms: %d\n", (int)alarm_count);

    printf(
        "Total execution time: %.0f seconds\n",
        difftime(end_time, start_time)
    );

    exit(0);
}

int main()
{
    start_time = time(NULL);

    signal(SIGALRM, alarm_handler);
    signal(SIGINT, interrupt_handler);

    alarm(1);

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