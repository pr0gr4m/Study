#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

typedef struct net_message {
    int str_len;
    char message[BUF_SIZE];
} inet_message;

int main(int argc, char *argv[])
{
    int sock;
    char buf[BUF_SIZE];
    struct net_message send_msg, recv_msg;
    int recv_len, recv_cnt;
    struct sockaddr_in serv_addr;
    int i;

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
        puts("Connected.............");

    for(i=0; i<3; i++)
    {
        memset(&send_msg, 0, sizeof(send_msg));
        memset(&recv_msg, 0, sizeof(recv_msg));

        /* Send message */
        fputs("Input message : ", stdout);
        fgets(buf, BUF_SIZE, stdin);
        send_msg.str_len = strlen(buf);
        strcpy(send_msg.message, buf);
        write(sock, &send_msg, send_msg.str_len + 4);
        
        /* receive message */
        read(sock, &recv_msg.str_len, 4);
        recv_len = 0;
        while(recv_msg.str_len > recv_len)
        {
            recv_cnt = read(sock, &recv_msg.message[recv_len], BUF_SIZE - recv_len);
            recv_len += recv_cnt;
        }
        printf("Receive Message : %s \n", recv_msg.message);
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
