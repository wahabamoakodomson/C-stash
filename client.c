#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <port> \n", argv[0]);

		return -1;
	}

	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);

	int sockfd;
	struct sockaddr_in addr;
	char send_data[1024],recv_data[1024];
	socklen_t addr_size;
	int n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("[-] socket error\n");

		return -2;
	}

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	

	bzero(send_data, 1024);
	strcpy(send_data, "Hello World");
	sendto(sockfd, send_data, 1024, 0, (struct sockaddr *)&addr, 
	sizeof(addr));

	bzero(recv_data, 1024);
	addr_size = sizeof(addr);
	recvfrom(sockfd, recv_data, 1024, 0, (struct sockaddr *)&addr,
	&addr_size);
	printf("%s \n", recv_data);

	return 0;
}