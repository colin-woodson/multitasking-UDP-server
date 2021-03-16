#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"

int main()
{
    int port = atoi("6666");
    int ip = inet_addr("192.168.1.77");

    int client_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_sock < 0)
    {   
        perror("socket");
        exit(1);
    }   

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = ip; 

    char buf[1024];
//int i = 0;
    while(1)
    {   
        memset(buf, '\0', sizeof(buf));
        //printf("client# \n");
        fflush(stdout);
	uint16_t device_id = 20479;
	uint16_t fault_code = 65535;
	char name[64] = "AABBCCDDEEFF";
	uint64_t latest_unix_second = get_unix_time();
	memcpy(buf, &device_id, 2);
	memcpy(buf+2, &fault_code, 2);
	memcpy(buf+4, name, 64);
	memcpy(buf+68, &latest_unix_second, 8);
	//printf("name = %s\n", name);
	//printf("latest_unix_second = %lu\n", latest_unix_second);
	//printf("buf+12 = %lu\n", *(long unsigned int *)(buf+12));
        ssize_t size = sendto(client_sock, buf, sizeof(buf), 0, (struct sockaddr*)&server, sizeof(server));
        if(size < 0)
            perror("sendto");

	//printf("i = %d\n", i++);
	//sleep(1);
    }

    return 0;
}
