/*
 * Client.h
 *
 *  Client Implementation file
 *  Created on: November 9, 2023
 *  Author: Leonardo Birardi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client.h"

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

// Function prototypes
struct sockaddr_in bindSocket(struct sockaddr_in);
void checkWindowDevice();
void clearwinsock();
void closeConnection(int);
int connectToServer(int, struct sockaddr_in);
int createSocket(int);
void errorhandler(char*);
void inputString(char*);
int receiveData(int, int, char*);
int sendData(int, char*);


int main(int argc, char *argv[]) {
	// 0) Initialize the WSA library in case we are on Windows
	checkWindowDevice();

	// 1) Create a socket
	int c_socket = -1;
	c_socket = createSocket(c_socket);

	// 2) Bind the socket
	struct sockaddr_in sad = bindSocket(sad);

	// 3) Connect to the server
	connectToServer(c_socket, sad);

	// Receive Welcome Message
	receiveData(c_socket, sizeof(char) * BUFFERSIZE, msg);

	// 4) Send data
	while (1) {
		// Request data from the console
		inputString(msg);

		sendData(c_socket, msg);

		// 5) Receive data from the server
		receiveData(c_socket, sizeof(char) * BUFFERSIZE, msg);

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
 * @return 1 if the send operation is successful, -1 if there is an error.
 */
int sendData(int c_socket, char *msg) {
	// Send data to the server
	if (send(c_socket, msg, sizeof(sizeof(char) * BUFFERSIZE), 0)
			!= sizeof(sizeof(char) * BUFFERSIZE)) {
		errorhandler(
				"\nsend() sent a different number of bytes than expected.");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	}
	return 1;
}

/**
 * Receives data from the server through the given socket and stores it in msg.
 *
 * @param c_socket The socket for receiving data.
 * @param string_len The length of the string to receive.
 * @param msg The received message will be stored in this buffer.
 * @return 0 if data is received successfully, -1 if there is an error.
 */
int receiveData(int c_socket, int string_len, char *msg) {
	int bytes_received;
	int total_bytes_received = 0;

	memset(msg, 0, string_len); // Ensure any extra bytes are set to 0
	printf("Received: "); // Set up to print the received string

	while (total_bytes_received < string_len) {
		if ((bytes_received = recv(c_socket, msg + total_bytes_received,
				string_len - total_bytes_received, 0)) <= 0) {
			errorhandler(
					"\nrecv() failed or the connection closed prematurely.");
			closesocket(c_socket);
			clearwinsock();
			return -1;
		}
		total_bytes_received += bytes_received; // Keep track of the total received bytes
	}

	msg[total_bytes_received] = '\0'; // Null-terminate the received message

	printf("%s\n", msg);

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
	system("pause");
	getchar();
}

/**
 * Creates a TCP socket and initializes it.
 *
 * @param c_socket The socket to be created.
 * @return The created socket if successful, -1 if there is an error.
 */
int createSocket(int c_socket) {
	// Creation of a TCP socket
	c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c_socket < 0) {
		errorhandler("Socket creation failed.\n");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	} else {
		printf("Socket created successfully!\n");
	}
	return c_socket;
}

/**
 * Binds the socket to the specified address and port.
 *
 * @param sad The sockaddr_in structure containing address and port information.
 * @return The sockaddr_in structure after binding.
 */
struct sockaddr_in bindSocket(struct sockaddr_in sad) {
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;  // Set IPv4 socket
	sad.sin_addr.s_addr = inet_addr(PROTO_ADDR); // Server's IP
	sad.sin_port = htons(PROTOPORT); // Server's port

	return sad;
}

/**
 * Connects to the server using the provided socket and address.
 *
 * @param c_socket The socket to connect.
 * @param sad The sockaddr_in structure containing server address information.
 * @return 1 if the connection is successful, -1 if there is an error.
 */
int connectToServer(int c_socket, struct sockaddr_in sad) {
	if (connect(c_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
		errorhandler("Connection failed.\n");
		closesocket(c_socket);
		clearwinsock();
		return -1;
	} else {
		printf("Connection Established!\n");
		return 1;
	}
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
	printf("\nEnter the commands to send to the server: ");
	// Use fgets to read an entire line, including spaces
	fgets(msg, BUFFERSIZE, stdin);

	// Remove the trailing newline character if present
	size_t length = strlen(msg);
	if (length > 0 && msg[length - 1] == '\n') {
		msg[length - 1] = '\0';
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

