/*
 * Client.h
 *
 *  Client Implementation file
 *  Created on: December 10, 2023
 *  Author: Leonardo Birardi
 */

#include "Headers.h"
#include "Client.h"


// Function prototypes
struct sockaddr_in bindSocket(struct sockaddr_in, char*, int);
void checkWindowDevice();
void clearwinsock();
void closeConnection(int);
int createSocket(int);
void errorhandler(char*);
void inputString(char*);
int receiveData(int, char*, struct sockaddr_in*, struct sockaddr_in*);
int sendData(int, char*, struct sockaddr_in*);


int main(int argc, char *argv[]) {
	// 0) Initialize the WSA library in case we are on Windows
	checkWindowDevice();

	// 1) Create a socket
	int c_socket = -1;
	c_socket = createSocket(c_socket);
	printf("Server socket created successfully!\n");

	// 2) Sets address and port converting from name to address if name is passed as boot parameter
	char *host_input[2];
	struct hostent *host;
	struct in_addr *ina;
	unsigned portC;
	char *token;

	if(argc > 1){
		token = strtok(argv[1], ":");
		host_input[0] = token;
		host_input[1] = strtok(NULL, "\0");
	} else {
		host_input[0] = PROTO_ADDR; // default address (localhost)
		host_input[1] = PROTOPORT;  // default port
		printf("Address and port not entered, standard value applied\n");
	}

	// translate name into address
	host = gethostbyname((char*) host_input[0]);
	if(host){
		ina = (struct in_addr*) host->h_addr_list[0];
		portC = strtoul(host_input[1], NULL, 10);
		printf("Address resolved: %s:%u\n", inet_ntoa(*ina), portC);
	}else{
		printf("Address not resolved.\n");
		closeConnection(c_socket);
	}

	// 3) Bind the socket
	struct sockaddr_in echoServAddr = bindSocket(echoServAddr, inet_ntoa(*ina), portC);
	struct sockaddr_in fromAddr;
	printf("Server socket binded successfully!\n");

	// Client loop operations
	while (1) {
		// Request data from the console
		inputString(msg);

		// 4) send data to server
		sendData(c_socket, msg, &echoServAddr);

		// 5) Receive data from the server
		receiveData(c_socket, msg, &fromAddr, &echoServAddr);

		// Check if the received message is "Bye"
		char *byeString = "Bye";
		if (strcmp(msg, byeString) == 0) {
			break; // Exit the loop if the server sends "Bye"
		}
	}

	// 6) Close the connection
	closeConnection(c_socket);

	return 0;
}

/**
 * Displays an error message to the console.
 *
 * @param error_message The error message to display.
 */
void errorhandler(char *error_message) {
	printf("%s", error_message);
}

/**
 * Cleans up Windows socket resources if on a Windows platform.
 */
void clearwinsock() {
#if defined WIN32
	WSACleanup();
#endif
}

/**
 * Sends data to the server through the given socket.
 *
 * @param c_socket The socket for sending data.
 * @param msg The message to be sent.
 * @param echoServAddr The sockaddr_in structure containing the server's information.
 * @return 1 if the send operation is successful, -1 if there is an error.
 */
int sendData(int c_socket, char *msg, struct sockaddr_in *echoServAddr) {
	// Send data to the server
	int echoStringLen = strlen(msg);
	if (sendto(c_socket, msg, echoStringLen, 0, (struct sockaddr*) echoServAddr, sizeof(*echoServAddr)) != echoStringLen) {
		errorhandler("\nsendto() sent a different number of bytes than expected.");
		return -1;
	}
	return 1;
}


/**
 * Receives data from the server through the given socket and stores it in msg.
 *
 * @param sock The socket for receiving data.
 * @param msg The received message will be stored in this buffer.
 * @param fromAddr The sockaddr_in structure containing the server's information.
 * @param echoServAddr The sockaddr_in structure containing the server's information.
 * @return 0 if data is received successfully, -1 if there is an error.
 */
int receiveData(int sock, char *msg, struct sockaddr_in *fromAddr, struct sockaddr_in *echoServAddr) {
	unsigned int fromSize = sizeof(*fromAddr);
	int respStringLen = recvfrom(sock, msg, BUFFERSIZE, 0, (struct sockaddr*) fromAddr, &fromSize);

	if (echoServAddr->sin_addr.s_addr != fromAddr->sin_addr.s_addr)
	{
		errorhandler("Error: received a packet from unknown source.\n");
		exit(EXIT_FAILURE);
	}
	msg[respStringLen] = '\0';

    // Convert the address to the associated DNS
    struct hostent *he;
    he = gethostbyaddr((char *)&fromAddr->sin_addr, sizeof(struct in_addr), AF_INET);
    if (he == NULL) {
        errorhandler("gethostbyaddr() failed\n");
        closesocket(sock);
        clearwinsock();
        return -1;
    }

    printf("\nReceived result from server %s, IP %s: %s\n", he->h_name, inet_ntoa(fromAddr->sin_addr), msg);
	return 0;
}


/**
 * Closes the connection and performs cleanup.
 *
 * @param c_socket The socket to close.
 */
void closeConnection(int c_socket) {
	closesocket(c_socket);
	clearwinsock();
	printf("\n");    // Print a final newline
#ifdef _WIN32
    system("pause");  // Windows specific command
#else
    getchar();  // Unix-like systems command
#endif
}

/**
 * Creates a UDP socket and initializes it.
 *
 * @param c_socket The socket to be created.
 * @return The created socket if successful, -1 if there is an error.
 */
int createSocket(int c_socket) {
	// Creation of a TCP socket
	if ((c_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		errorhandler("Socket creation failed.\n");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	}
	return c_socket;
}

/**
 * Binds the socket to the specified address and port.
 *
 * @param sad The sockaddr_in structure containing address and port information.
 * @param server_ip The server ip to bind the socket to.
 * @param port_number The port number to bind the socket to.
 * @return The sockaddr_in structure after binding.
 */
struct sockaddr_in bindSocket(struct sockaddr_in sad, char* server_ip, int port_number) {
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;  // Set IPv4 socket
	sad.sin_addr.s_addr = inet_addr(server_ip); // Server's IP
	sad.sin_port = htons(port_number); // Server's port
	return sad;
}

/**
 * Initializes the WSA library if on a Windows platform.
 */
void checkWindowDevice() {
#if defined WIN32
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		printf("Error during WSAStartup\n");
		return;
	}
#endif
}

/**
 * Reads and validates user input as a command string to send to the server.
 * If the input is invalid, it prompts the user to enter a valid input.
 *
 * @param msg The command string entered by the user.
 */
void inputString(char *msg) {
	memset(msg, 0, BUFFERSIZE);
	printf("\nEnter the commands to send to the server: ");

	// Use fgets to read an entire line, including spaces
	if (fgets(msg, BUFFERSIZE, stdin) != NULL) {
		// Check if the input exceeds BUFFERSIZE
		if (!strchr(msg, '\n')) {
			// Input exceeds BUFFERSIZE, clear the input buffer
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Input too long. Please enter commands less than %d characters.\n", BUFFERSIZE);
		} else {
			// Remove the trailing newline character if present
			size_t length = strlen(msg);
			if (length > 0 && msg[length - 1] == '\n') {
				msg[length - 1] = '\0';
			}
		}
	} else {
	    // fgets failed, handle the error
	    printf("Error reading input.\n");
	}

	// Check if the input string length is within limits
	if (strlen(msg) > (BUFFERSIZE - 1)) {
		printf(
				"\nInput string is too long, a string truncated according to the limits will be sent to the server.\n");
		msg[BUFFERSIZE - 1] = '\0'; // Truncate the string if it's too long
	}

	// Check if the input string format is valid (operator value value)
	// Regex for all devices
	char operator;
	int num1, num2;
	if (sscanf(msg, "%c", &operator) == 1 && strchr("=", operator) != NULL) {
		printf("\nClosing the connection...\n");
	} else {
		if (sscanf(msg, "%c %d %d", &operator, &num1, &num2) != 3||
		strchr("+-*/", operator) == NULL) {
			printf(
					"\nInvalid input format. Please use the format: operator[+-*/] value value or = to close the connection\n");
			inputString(msg); // Prompt the user to enter a valid input
		}
	}
}

