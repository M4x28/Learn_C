/*
 * Server.c
 *
 *	Server Implementation file
 *  Created on: December 10, 2023
 *  Author: Leonardo Birardi
 */

#include "Headers.h"
#include "Server.h"
#include "Calculator.h"

// Function prototypes
struct sockaddr_in bindSocket(int, struct sockaddr_in, const char*, const int);
void checkWindowDevice();
void clearwinsock();
void closeConnection(int);
int createSocket(int);
void errorhandler(char*);
void processData(char*);

int main(int argc, char *argv[]) {
	// 0) Initialize the WSA library in case we are on Windows
	checkWindowDevice();

	// 1) Create a socket
	int my_socket = -1;
	my_socket = createSocket(my_socket);
	printf("Server socket created successfully!\n");

	// 2) Bind the socket
	struct sockaddr_in sad = bindSocket(my_socket, sad, PROTO_ADDR, PROTOPORT);
	printf("Server socket binded successfully!\n");
	struct sockaddr_in cad;	// Structure for the client's address

	printf("Searching for a client...\n");

	// Server loop operations
	while(1) {
		// Receive and process data from the client until the client sends "="
		socklen_t client_len = sizeof(cad); // Set the client's size
		memset(msg, 0, BUFFERSIZE); // clean msg
		int bytes_received = recvfrom(my_socket, msg, BUFFERSIZE, 0, (struct sockaddr*) &cad, &client_len);	// 3) receive data

		// check the received data length
		if (bytes_received <= 0) {
			if (bytes_received == 0) {
				printf("Client has closed the connection.\n");
			} else {
				errorhandler("recvfrom() failed or connection closed prematurely\n");
			}
		} else {
			// 4) Convert the address to the associated DNS
			struct hostent *he;
			he = gethostbyaddr((char *)&(cad.sin_addr), sizeof(struct in_addr), AF_INET);
			if (he == NULL) {
			    errorhandler("gethostbyaddr() failed\n");
			    closesocket(my_socket);
			    clearwinsock();
			    return -1;
			}

			printf("\nRequest operation '%s' from client %s, IP %s\n", msg, he->h_name, inet_ntoa(cad.sin_addr));

			// 5) Process data according to the logic defined in the function
			processData(msg);

			printf("\n%s\n", msg);

			// 6) Send processed data back to the client
			if (sendto(my_socket, msg, sizeof(msg), 0, (struct sockaddr*) &cad, client_len) != sizeof(msg)) {
				errorhandler("sendto() sent a different number of bytes than expected\n");
				closesocket(my_socket);
				clearwinsock();
				return 0;
			}
		}
	}

	// Close the socket
	closeConnection(my_socket);
}

/**
 * Checks and initializes the Windows Socket API (WSA) for Windows systems.
 * This function is used for cross-platform compatibility.
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
    printf("Press any key to close the process...");
    getchar();  // Unix-like systems command
#endif
}

/**
 * Creates a socket for communication with the server.
 *
 * @param my_socket The socket descriptor to be created.
 * @return The created socket descriptor on success, -1 on failure.
 */
int createSocket(int my_socket) {
	if ((my_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		errorhandler("socket() failed.\n");
		clearwinsock();
		return -1;
	}
    return my_socket;
}

/**
 * Binds the socket to a specific address and port.
 *
 * @param my_socket The socket descriptor to bind.
 * @param sad A sockaddr_in structure containing address and port information.
 * @param server_addr Server Address
 * @param port_number Server port
 * @return The sockaddr_in structure with updated information after binding.
 */
struct sockaddr_in bindSocket(int my_socket, struct sockaddr_in sad, const char* server_addr, const int port_number) {
	// Assign an address to the newly created socket
    memset(&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr(server_addr);
    sad.sin_port = htons(port_number);

    if (bind(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
        errorhandler("bind() failed.\n");
        closesocket(my_socket);
        clearwinsock();
    }

    return sad;
}


/**
 * Cleans up resources related to the Windows Socket API (WSA).
 * This function is used for cross-platform compatibility.
 */
void clearwinsock() {
#if defined WIN32
    WSACleanup();
#endif
}

/**
 * Handles errors by printing the error message to the console.
 *
 * @param errorMessage The error message to display.
 */
void errorhandler(char *errorMessage) {
    printf("%s", errorMessage);
}

/**
 * Processes the input message, performs calculations, and updates the input string.
 *
 * @param msg The input message containing operator and operands.
 */
void processData(char *msg) {
    // Extract the operator and operands from the input string
    char operator = msg[0];

    // Check if the operator is '=' to terminate communication
    if (operator == '=') {
        char *byeString = "Bye";
        snprintf(msg, strlen(byeString) + 1, "%s", byeString);
        return;
    }

    int numOperands = 0;
    int operands[MAXOPERANDS];

    // Tokenize the input string and collect operands
    char *token = strtok(msg + 2, " ");
    while (token != NULL && numOperands < MAXOPERANDS) {
        if (sscanf(token, "%d", &operands[numOperands]) != 1) {
            // Error handling: Invalid operand format
            snprintf(msg, strlen(msg), "Invalid operand format: %s", token);
            return; // Or handle the error as needed
        }
        numOperands++;
        token = strtok(NULL, " ");
    }

    if (numOperands < 2) {
        char *insufficientNumberError = "Insufficient number of operands";
        strcpy(msg, insufficientNumberError);
        return;
    }

    double result = operands[0];
    for (int i = 1; i < numOperands; i++) {
        switch (operator) {
            case '+':
                result = add(result, operands[i]);
                break;
            case '-':
                result = sub(result, operands[i]);
                break;
            case '*':
                result = mult(result, operands[i]);
                break;
            case '/':
                if (operands[i] != 0) {
                    result = division(result, operands[i]);
                } else {
                    // Error handling: Division by zero
                    char *divisionError = "Division by Zero Error";
                    strcpy(msg, divisionError);
                    return;
                }
                break;
            default:
                // Error handling: Unknown operator
                snprintf(msg, BUFFERSIZE, "Unknown operator: %c", operator);
                return;
        }
    }

    // Convert the result to a string and update the input string
        snprintf(msg, BUFFERSIZE, "%d %c %d = %.2f", operands[0], operator, operands[1], result);
}
