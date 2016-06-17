#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define FILE_SZ 26
#define BUF_SIZE 1024
#define MSG_SIZE sizeof(unsigned long)

typedef struct net_message
{
    unsigned long size;
    char buf[BUF_SIZE];
} inet_message;

void error_handling(char *message);
void recv_file(int socket, FILE *fp);

int main(int argc, char *argv[])
{
    int sock;
    struct net_message file_name;
    struct sockaddr_in serv_addr;
    FILE *fp;
    char isSuccess;
    char tmp[] = "copy_";
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
        puts("Connected........");
    
    memset(&file_name, 0, sizeof(file_name));

    fputs("Input File Name : ", stdout);
    gets(file_name.buf);
    file_name.size = strlen(file_name.buf);

    write(sock, &file_name.size, MSG_SIZE);
    write(sock, file_name.buf, file_name.size);
    
    memmove(file_name.buf+5, file_name.buf, file_name.size + 1);
    memcpy(file_name.buf, tmp, strlen(tmp));

    read(sock, &isSuccess, 1);
    if(isSuccess == 'T')
        fp = fopen(file_name.buf, "wb");
    else
        error_handling("file open error");

    recv_file(sock, fp);
    fclose(fp);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void recv_file(int sock, FILE *fp)
{
    char buf[BUF_SIZE];
    int recv_len;
    long fsize, cur_len;

    read(sock, &fsize, sizeof(long));
    cur_len = 0;
    while(fsize > cur_len)
    {
        recv_len = read(sock, buf, BUF_SIZE);
        cur_len += recv_len;
        fwrite(buf, 1, recv_len, fp);
    }
}
