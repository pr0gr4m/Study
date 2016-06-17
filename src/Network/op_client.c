#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    int i, count;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    int result;

    if(argc != 3) {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");
    else
        puts("Connected...............");

    fputs("Operand count : ", stdout);
    scanf("%d", &count);
    message[0] = (char)count;

    for(i=0; i<count; i++)
    {
        printf("Operand %d : ", i + 1);
        scanf("%d", (int*)&message[i * 4 + 1]);
    }
    getchar();

    fputs("Operator : ", stdout);
    scanf("%c", &message[count * 4 + 1]);

    write(sock, message, count * 4 + 2);
    read(sock, &result, 4);

    printf("Operation result : %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
