#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);
int calculate(int *arr, int len, char op);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    int i, recv_len = 0, recv_cnt;
    socklen_t clnt_addr_size;
    char cnt;
    char opinfo[BUF_SIZE];
    int result;


    if(argc != 2)
    {
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

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    clnt_addr_size = sizeof(clnt_addr);
    for(i=0; i<5; i++)
    {
        cnt = 0;
        recv_len = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

        if(clnt_sock == -1)
            error_handling("accept() error");

        read(clnt_sock, &cnt, 1);
        
        while(recv_len < (cnt * 4 + 1)) {
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
            recv_len += recv_cnt;
        }

        result = calculate((int*)opinfo, cnt, opinfo[recv_len - 1]);
        write(clnt_sock, &result, 4);

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

int calculate(int *arr, int len, char op)
{
    int num = *arr;
    int i;

    switch(op)
    {
        case '+':
            for(i=1; i<len; i++)
                num += arr[i];
            break;
        case '-':
            for(i=1; i<len; i++)
                num -= arr[i];
            break;
        case '*':
            for(i=1; i<len; i++)
                num *= arr[i];
            break;
        default:
            error_handling("operator error");
            break;
    }

    return num;
}
