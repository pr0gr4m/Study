#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in adr;
    pid_t pid;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    pid = fork();

    if (pid == 0)
    {
        printf("child descripter : %d \n", sock);
        close(sock);
    }
    else
    {
        printf("parent descripter : %d \n", sock);
        close(sock);
    }

    return 0;
}
