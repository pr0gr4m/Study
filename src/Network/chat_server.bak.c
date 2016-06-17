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
    int serv_sock, clnt_sock;
    char buf[BUF_SIZE];
    struct net_message recv_msg, send_msg;
    int recv_cnt, recv_len;
    int i, j;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    if(argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);

    for(i=0; i<5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        
        for(j=0; j<3; j++)
        {
            memset(&recv_msg, 0, sizeof(recv_msg));
            memset(&send_msg, 0, sizeof(send_msg));

            /* Receive message */
            read(clnt_sock, &recv_msg.str_len, 4);

            recv_len = 0;
            while(recv_msg.str_len > recv_len)
            {
                recv_cnt = read(clnt_sock, &recv_msg.message[recv_len], BUF_SIZE - recv_len);
                recv_len += recv_cnt;
            }
            printf("Receive from client : %s \n", recv_msg.message);
            
            /* send message */
            fputs("Input String : ", stdout);
            fgets(buf, BUF_SIZE, stdin);
            send_msg.str_len = strlen(buf);
            strcpy(send_msg.message, buf);
            write(clnt_sock, &send_msg, send_msg.str_len + 4);
        }
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
