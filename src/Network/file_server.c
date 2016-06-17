#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define FILE_SZ 26
#define BUF_SIZE 1024
#define MSG_SIZE sizeof(unsigned long)
void error_handling(char *message);
void send_file(int sock, FILE *fp);

typedef struct net_message {
    unsigned long size;
    char buf[BUF_SIZE];
} inet_message;

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct net_message file_name;
    FILE *fp;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int i;
    int recv_len, recv_cnt;
    char table[2] = {'T', 'F'};
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
        memset(&file_name, 0, sizeof(file_name));
        read(clnt_sock, &file_name.size, MSG_SIZE);

        recv_len = 0;
        while(file_name.size > recv_len)
        {
            recv_cnt = read(clnt_sock, &file_name.buf[recv_len], BUF_SIZE - recv_len);
            recv_len += recv_cnt;
        }
        
        fp = fopen(file_name.buf, "rb");
        if(fp == NULL) {
            fputs("There isn't that file... \n", stderr);
            write(clnt_sock, &table[1], 1);
            close(clnt_sock);
            continue;
        }
        else
            write(clnt_sock, &table[0], 1);
        
        send_file(clnt_sock, fp);
        fclose(fp);
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

void send_file(int sock, FILE *fp)
{
    char buf[BUF_SIZE];
    int readCnt;
    long fsize;

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    write(sock, &fsize, sizeof(long));
    while(1)
    {
        readCnt = fread(buf, 1, BUF_SIZE, fp);
    
        if(readCnt < BUF_SIZE)
        {
            if(feof(fp))
            {
                write(sock, buf, readCnt);
                puts("File send complete!");
                break;
            }
            else
                error_handling("file send error");
        }
        write(sock, buf, BUF_SIZE);
    }
}
