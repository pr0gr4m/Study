#include <stdio.h>
#include <arpa/inet.h>
#include "dumpcode.h"

int main(int argc, char *argv[])
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port : %#x \n", host_port);
    printf("Network ordered port : %#x \n", net_port);
    printf("Host ordered address : %#x \n", host_addr);
    printf("Network ordered address : %#x \n", net_addr);
    printf("Address of host_port : %#p \n", &host_port);
    printf("Address of net_port : %#p \n", &net_port);
    printf("Address of host_addr : %#p \n", &host_addr);
    printf("Address of net_addr : %#p \n", &net_addr);
    printf("------------ dumpcode ------------- \n");
    dumpcode((unsigned char *)&host_port, 100);
    printf("----------------------------------- \n");

    return 0;
}
