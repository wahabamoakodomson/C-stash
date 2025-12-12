#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <port> \n", argv[0]);

		return -1;
	}

	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);

	int sockfd;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];
	socklen_t addr_size;
	int n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0) {
		perror("[-] socket error\n");

		return -2;
	}

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);

	n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	if (n < 0) {
		perror("[-]bind error");

		return -2;
	}
	while (1) {
		// Receive data
		bzero(buffer, 1024);
		addr_size = sizeof(client_addr);
		recvfrom(sockfd, buffer, 1024, 0, 
		(struct sockaddr *)&client_addr, &addr_size);
		printf("data received: %s \n", buffer);


		// Send data
		bzero(buffer, 1024);
		strcpy(buffer, "Welcome to Compu-Zed");
		sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr,
		sizeof(client_addr));
	}




	return 0;
}