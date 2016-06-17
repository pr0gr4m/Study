#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define BUF_SIZE 30

void read_childproc(int sig);

int main(int argc, char *argv[])
{
    int fds1[2], fds2[2];
    char str1[] = "First string~";
    char str2[] = "Second string!";
    char str3[] = "Thired string...";
    char buf[BUF_SIZE];
    int state;
    pid_t pid;
    struct sigaction act;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

    pipe(fds1), pipe(fds2);
    
    pid = fork();

    if (pid == 0)
    {
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("child proc output : %s \n", buf);
        write(fds1[1], str3, sizeof(str3));

        return 0;
    }
    else
    {
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc output1 : %s \n", buf);
        write(fds2[1], str2, sizeof(str2));
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc output2 : %s \n", buf);

        return 0;
    }
}

void read_childproc(int sig)
{
    int status;
    pid_t pid;
    pid = waitpid(-1, &status, WNOHANG);

    if (WIFEXITED(status))
    {
        printf("removed proc id : %d \n", pid);
        printf("return valud : %d \n", WEXITSTATUS(status));
    }
}
