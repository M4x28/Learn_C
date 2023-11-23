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
void errorhandler(char *error_message);
void clearwinsock();
int sendData(int, msg*);
void receiveData(int, int);
void closeConnection(int);
int createSocket(int);
struct sockaddr_in bindSocket(struct sockaddr_in);
int connectToServer(int, struct sockaddr_in);
void checkWindowDevice();
void inputStrings(msg*, int);

int main(int argc, char *argv[]) {
    // 0) Initialize the WSA library in case we are on Windows
    checkWindowDevice();

    // 1) Create a socket
    int c_socket = -1;
    c_socket = createSocket(c_socket);

    // 2) Bind the socket
    struct sockaddr_in sad;
    sad = bindSocket(sad);

    // 3) Connect to the server
    connectToServer(c_socket, sad);

    // 4) Send data
    msg m;
    int n;
    printf("Enter the number of data to send: ");
    scanf("%d", &n);
    inputStrings(&m, n);
    sendData(c_socket, &m);

    // 5) Receive data from the server
    receiveData(c_socket, sizeof(m));

    // 6) Close the connection
    closeConnection(c_socket);

    return 0;
}

void errorhandler(char *error_message) {
    printf("%s", error_message);
}

void clearwinsock() {
#if defined WIN32
    WSACleanup();
#endif
}

int sendData(int c_socket, msg *m) {
    // Send data to the server
    if (send(c_socket, m, sizeof(msg), 0) != sizeof(msg)) {
        errorhandler("send() sent a different number of bytes than expected.");
        closesocket(c_socket);
        clearwinsock();
        return -1;
    }
    return 1;
}

void receiveData(int c_socket, int string_len) {
    int bytes_received;
    int total_bytes_received = 0;
    char buf[BUFFERSIZE];   // Buffer for data from the server
    memset(buf, 0, BUFFERSIZE); // Ensure any extra bytes are set to 0
    printf("Received: "); // Set up to print the received string

    while (total_bytes_received < string_len) {
        if ((bytes_received = recv(c_socket, buf, BUFFERSIZE - 1, 0)) <= 0) {
            errorhandler("recv() failed or the connection closed prematurely.");
            closesocket(c_socket);
            clearwinsock();
            return;
        }
        total_bytes_received += bytes_received; // Keep track of the total received bytes
    }
    buf[bytes_received] = '\0'; // Redundant but sets the null terminator

    char dataCopy[DATASIZE + 1]; // Copy of the data field
    strncpy(dataCopy, buf, DATASIZE);
    dataCopy[DATASIZE] = '\0'; // Ensure it's null-terminated

    char *token = strtok(dataCopy, "()");
    while (token != NULL) {
        printf("Substring: %s\n", token);
        token = strtok(NULL, "()");
    }
}

void closeConnection(int c_socket) {
    closesocket(c_socket);
    clearwinsock();
    printf("\n");    // Print a final newline
    system("pause");
    getchar();
}

int createSocket(int c_socket) {
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

struct sockaddr_in bindSocket(struct sockaddr_in sad) {
    memset(&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP
    sad.sin_port = htons(PROTOPORT); // Server's port

    return sad;
}

int connectToServer(int c_socket, struct sockaddr_in sad) {
    if (connect(c_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
        errorhandler("Connection failed.\n");
        closesocket(c_socket);
        clearwinsock();
        return -1;
    } else {
        printf("Connected\n");
        return 1;
    }
}

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

void inputStrings(msg *m, int n) {
    // Initialize all fields to zero
    memset(m->data, 0, DATASIZE);
    memset(m->operator, 0, OPERATORSIZE);
    memset(m->option, 0, OPTIONSIZE);

    for (int i = 0; i < n; i++) {
        char input[DATASIZE];
        printf("String %d: ", i + 1);
        scanf("%s", input);

        // Check if the data buffer is full
        if (strlen(m->data) + strlen(input) + 1 >= DATASIZE) {
            printf("The data buffer is full. No more strings can be added.\n");
            break;
        }

        // Add the string to the data field with the escape character
        strcat(m->data, input);
        strcat(m->data, "()"); // Using the escape character
    }

    // Ask the user to input the operator field if necessary
    printf("Enter the operator field (up to %d characters, optional): ", OPERATORSIZE - 1);
    scanf("%s", m->operator);

    // Check for the maximum length of the operator field
    if (strlen(m->operator) > OPERATORSIZE - 1) {
        printf("The operator field is too long. Limit of %d characters. It will be cleared.\n", OPERATORSIZE - 1);
        memset(m->operator, 0, OPERATORSIZE); // Clear the field
    }

    // Ask the user to input the option field if necessary
    printf("Enter the option field (up to %d characters, optional): ", OPTIONSIZE - 1);
    scanf("%s", m->option);

    // Check for the maximum length of the option field
    if (strlen(m->option) > OPTIONSIZE - 1) {
        printf("The option field is too long. Limit of %d characters. It will be cleared.\n", OPTIONSIZE - 1);
        memset(m->option, 0, OPTIONSIZE); // Clear the field
    }
}
