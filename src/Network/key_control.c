#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void key_control(int sig);

int main(int argc, char *argv[])
{
    int i, j;
    struct sigaction act;

    act.sa_handler = key_control;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    for(i = 1; i < 9; i++)
    {
        for(j = 1; j < 9; j++)
        {
            printf("%d x %d = %d \n", i, j, i * j);
            sleep(1);
        }
    }

    return 0;
}

void key_control(int sig)
{
    int key;

    if (sig == SIGINT)
    {
        fputs("Do you want to exit? (Y / n) : ", stdout);
        key = getchar();
        getchar();

        if (key == 'Y' || key == 'y')
            exit(1);
    }
}
