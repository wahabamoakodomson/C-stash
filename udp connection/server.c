#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE (1024)

// Main server program for handling UDP requests to manage computer bookings.
// Sets up a UDP socket, loads computer data from file, listens for commands,
// validates input, manages bookings, and responds with appropriate messages.
int main(int argc, char **argv)
{
	int sockfd, n, port;
	socklen_t addr_size;
	struct sockaddr_in server_addr, client_addr;
	char send_data[BUFSIZE], recv_data[BUFSIZE];

	if (argc < 2) {
		printf("Error, too few arguments\n");
		printf("Call with: udpserver <host-ip>\n");
		printf("Example: ./udpclient 5000\n");

		return -1;
	}

	port = atoi(argv[1]);

	// Create UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("[-] socket error\n");

		return -2;
	}

	// Zero out server address structure and set family, port, and bind to
	// all interfaces
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind socket to the server address
	n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (n < 0) {
		perror("[-]bind error");

		return -2;
	}

	// Main loop to handle incoming requests
	while (1) {
		// Prepare to receive response from the client
		bzero(recv_data, BUFSIZE);
		addr_size = sizeof(client_addr);
		// Receive data from client
		recvfrom(sockfd, recv_data, BUFSIZE, 0,
			 (struct sockaddr *)&client_addr, &addr_size);
		printf("%s\n", recv_data);

		// sending data back to client
		snprintf(send_data, BUFSIZE, "Connected to server.");
		sendto(sockfd, send_data, strlen(send_data), 0,
		       (struct sockaddr *)&client_addr, addr_size);

		// break after successful sending and receiving just once
		break;
	}

	// Close the socket before exiting
	close(sockfd);

	return 0;
}
