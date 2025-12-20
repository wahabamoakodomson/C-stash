#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFSIZE (1024)

// Entry point for the UDP client application.
// Arguments:
// argc - number of command-line arguments.
// argv - array of command-line argument strings.
// Return: 0 on normal termination, negative values on error.
int main(int argc, char **argv)
{
	// Socket file descriptor and number of bytes received
	int sockfd, n;

	// Server address structure
	struct sockaddr_in addr;

	// Size of the address structure
	socklen_t addr_size;

	// Server IP address & port no provided via command-line argument
	char *ipaddr = argv[1];
	int port = atoi(argv[2]);

	// Buffers for sending and receiving;
	char send_data[BUFSIZE], recv_data[BUFSIZE];

	// Ensure the server IP address is provided
	if (argc < 3) {
		printf("Error, too few arguments\n");
		printf("Call with: udpclient <host-ip> <port no>\n");
		printf("udpclient 127.0.0.1 5000 for your local machine\n");

		return -1;
	}

	// Create a UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("[-] socket error");

		return -2;
	}

	// Initialize and configure the server address structure
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ipaddr, &addr.sin_addr);

	// Main interaction loop
	while (1) {

		// Send to the server
		snprintf(send_data, BUFSIZE, "Client connected.");
		sendto(sockfd, send_data, strlen(send_data), 0,
		       (struct sockaddr *)&addr, sizeof(addr));


		// Prepare to receive response from the server
		bzero(recv_data, BUFSIZE);
		addr_size = sizeof(addr);
		// Receive server response
		recvfrom(sockfd, recv_data, sizeof(recv_data) - 1, 0,
			 (struct sockaddr *)&addr, &addr_size);
		printf("%s\n", recv_data);


		// break after successful sending and receiving just once
		break;

	}

	// Close the socket before exiting
	close(sockfd);

	return 0;
}
