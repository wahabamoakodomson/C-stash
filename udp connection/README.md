# UDP Client–Server Example (C)

This project demonstrates a **simple UDP client and server** written in C using POSIX sockets.  
The client sends a single message to the server, the server responds once, and both programs exit.

This is intended as a **learning example** for understanding:
- UDP sockets
- `sendto()` / `recvfrom()`
- Basic client–server communication
- Socket address configuration

---

## Project Structure
"
├── client.c # UDP client source code
| 
├── server.c # UDP server source code
| 
├── build.sh # Build script
| 
└── README.md # Project documentation
"

---

## Requirements

- Linux or Unix-like operating system
- GCC compiler
- POSIX-compliant networking headers

---

## Build Instructions

Use the provided build.sh script:
- chmod +x build.sh
- ./build.sh

This will generate two binaries: 
- udpclient
- udpserver

---

## Running the Server

Start the server first. It listens on a UDP port and waits for a single client message.

- ./udpserver <port>

Example:
- ./udpserver 5000

The server:
- Binds to INADDR_ANY
- Receives one message from a client
- Sends a response back
- Exits after one request

---
## Running the Client

Run the client in another terminal (or machine).
- ./udpclient <server-ip> <port>

Example (local machine):
- ./udpclient 127.0.0.1 5000

The client:
- Sends "Client connected." to the server
- Waits for a response
- Prints the server message
- Exits

---

## Example Output

Server Terminal
- Client connected.

Client Terminal
- Connected to server.

---

## How It Works

### Client Flow
- Creates a UDP socket
- Builds the server address using IP and port
- Sends a message using sendto()
- Waits for a reply using recvfrom()
- Prints the response and exits

### Server Flow
- Creates a UDP socket
- Binds to a port on all interfaces
- Waits for a client message using recvfrom()
- Sends a response back to the client using sendto()
- Exits after one exchange

---

## Notes About UDP
- UDP is connectionless
- No guarantee of delivery, order, or duplication prevention
- Faster and simpler than TCP
- Suitable for real-time systems, games, and lightweight
  messaging

This example intentionally keeps things simple by:
- Handling only one request
- Not validating packet loss
- Not looping for multiple clients

---

## License

This project is provided for educational purposes.
Feel free to modify and extend it as needed.
