#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE    128
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    while(1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        str_len = recvfrom(sock, message, BUF_SIZE - 1, 0,
                (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(str_len == -1)
            error_handling("recvfrom() error");

        message[str_len] = 0;
        printf("Message from client : %s", message);

        fputs("Insert message(q to quit) : ", stdout);
        fgets(message, BUF_SIZE - 1, stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        sendto(sock, message, strlen(message), 0,
                (struct sockaddr*)&clnt_adr, sizeof(clnt_adr));
    }
    
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
