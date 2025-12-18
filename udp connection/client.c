#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

// Define the size of the buffer for incoming/outgoing data
#define BUFFERSIZE (1024)


// main - Entry point for UDP server program
// Args:
//	argc - Number of command-line arguments (should be 3: program name, IP 
//	address, port)
//	argv - Array of command-line argument strings:
//	argv[1]: IP address to bind the UDP server to (e.g., "127.0.0.1")
//	argv[2]: Port number to bind the UDP server to (e.g., "8080")
// Returns:
//	0 on successful execution
//	-1 if socket creation or argument validation fails
//	-2 if binding the socket to the IP/port fails
int main(int argc, char **argv)
{
	// Check if IP address and port are provided as command-line arguments
	if (argc < 3) {
		printf("Usage: %s <ip-address> <port> \n", argv[0]);
		return -1;
	}

	char *ip = argv[1];		// IP address to bind the socket to
	int port = atoi(argv[2]);	// Port number to bind the socket to

	int sockfd, n;
	char buffer[BUFFERSIZE];	// Buffer for data transfer
	socklen_t addr_size;
	struct sockaddr_in server_addr, client_addr;

	// Create a UDP socket (SOCK_DGRAM)
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("[-] socket error\n");
		return -1;
	}

	// Initialize server address structure with zeros
	memset(&server_addr, '\0', sizeof(server_addr));
	
	// IPv4 address family
	server_addr.sin_family = AF_INET;

	// Convert port number to network byte order
	server_addr.sin_port = htons(port);

	// Convert IP string to network address
	server_addr.sin_addr.s_addr = inet_addr(ip); 


	// Bind the socket to the specified IP address and port
	n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (n < 0) {
		perror("[-]bind error");
		return -2;
	}

	// Infinite loop to receive and respond to incoming UDP messages
	while (1) {
		// Clear the buffer before receiving data
		bzero(buffer, BUFFERSIZE);

		// Size of the client address structure
		addr_size = sizeof(client_addr);

		// Receive data from a client; store sender address in 
		// client_addr
		recvfrom(sockfd, buffer, BUFFERSIZE, 0,
			 (struct sockaddr *)&client_addr, &addr_size);

		// Print the received data
		printf("data received: %s \n", buffer);

		// Clear buffer before sending response
		bzero(buffer, BUFFERSIZE);

		// Prepare response message
		strcpy(buffer, "Welcome");

		// Send response back to the client
		sendto(sockfd, buffer, BUFFERSIZE, 0,
		       (struct sockaddr *)&client_addr, sizeof(client_addr));
	}

	return 0;
}
