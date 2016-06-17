#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 30

void *echo_clnt(void *arg);
void error_handling(char *msg);

char buf[BUF_SIZE];
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	pthread_t t_id;

	if (argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutex, NULL);
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	while (1)
	{
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if (clnt_sock == -1)
			error_handling("accept() error");

		pthread_create(&t_id, NULL, echo_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client : %d \n", clnt_sock);
	}

	close(serv_sock);
	pthread_mutex_destroy(&mutex);
	return 0;
}

void *echo_clnt(void *arg)
{
	int sock = *((int*)arg);
	int str_len;

	while (1)
	{
		pthread_mutex_lock(&mutex);
		str_len = read(sock, buf, BUF_SIZE);
		if (str_len == -1)
			return (void*)-1;
		if (str_len == 0)
			break;
		write(sock, buf, str_len);
		pthread_mutex_unlock(&mutex);
	}

	close(sock);
	return NULL;
}

void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
