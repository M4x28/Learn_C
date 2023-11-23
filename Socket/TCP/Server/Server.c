#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Server.h"

#if defined WIN32
#include <winsock.h>
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close
#endif

void errorhandler(char *errorMessage);
void clearwinsock();
void checkWindowDevice();
int createSocket(int my_socket);
void processData(msg *m);
struct sockaddr_in bindSocket(int my_socket, struct sockaddr_in);
void setSocketOnListen(int my_socket);

int main(int argc, char *argv[]) {
    // 0) Initialize the WSA library in case we are on Windows
    checkWindowDevice();

    // 1) Create a socket
    int my_socket = -1;
    my_socket = createSocket(my_socket);

    // 2) Bind the socket
    struct sockaddr_in sad;
    sad = bindSocket(my_socket, sad);

    // 3) Set the socket to listen mode
    setSocketOnListen(my_socket);

    struct sockaddr_in cad;    // Structure for the client's address
    int client_socket;     // Socket descriptor for the client
    int client_len;     // Size of the client's address

    char *input_string = "Connection Established!"; // String to send
    int string_length = strlen(input_string); // Calculate the length

    while (1) {
        printf("\nSearching for a client...");
        client_len = sizeof(cad); // Set the client's size

        // 4) Accept a connection
        if ((client_socket = accept(my_socket, (struct sockaddr*) &cad, &client_len)) < 0) {
            errorhandler("accept() failed.\n");
            closesocket(client_socket);
            clearwinsock();
            return 0;
        }

        // 5) Server sends a connection string
        send(client_socket, input_string, string_length, 0);
        printf("\nClient management %s\n", inet_ntoa(cad.sin_addr));

        // 6) Receive data from the client
        msg m;
        if ((recv(client_socket, &m, sizeof(msg), 0)) <= 0) {
            errorhandler("recv() failed or connection closed prematurely");
            closesocket(my_socket);
            clearwinsock();
        }

        // Print data sent by the client
        char dataCopy[DATASIZE + 1]; // Copy of the data field
        strncpy(dataCopy, m.data, DATASIZE);
        dataCopy[DATASIZE] = '\0'; // Ensure it's null-terminated

        char *token = strtok(dataCopy, "()");
        while (token != NULL) {
            printf("Substring: %s\n", token);
            token = strtok(NULL, "()");
        }

        // 7) Process data according to the logic defined in the function
        processData(&m);

        // 8) Send processed data back to the client
        if (send(client_socket, &m, sizeof(msg), 0) != sizeof(msg)) {
            errorhandler("send() sent a different number of bytes than expected");
            closesocket(my_socket);
            clearwinsock();
        }
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

int createSocket(int my_socket) {
    my_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (my_socket < 0) {
        errorhandler("Socket creation failed.\n");
        closesocket(my_socket);
        clearwinsock();
        return -1;
    } else {
        printf("Socket created successfully!\n");
    }
    return my_socket;
}

struct sockaddr_in bindSocket(int my_socket, struct sockaddr_in sad) {
    // Assign an address to the newly created socket
    memset(&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(PROTOPORT);

    if (bind(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
        errorhandler("bind() failed.\n");
        closesocket(my_socket);
        clearwinsock();
    }

    return sad;
}

void setSocketOnListen(int my_socket) {
    if (listen(my_socket, QUEUE < 0)) {
        errorhandler("listen() failed. \n");
        closesocket(my_socket);
        clearwinsock();
        return;
    }
}

void clearwinsock() {
#if defined WIN32
    WSACleanup();
#endif
}

void errorhandler(char *errorMessage) {
    printf("%s", errorMessage);
}

void processData(msg *m) {
    char dataCopy[DATASIZE + 1]; // Copy of the data field
    strncpy(dataCopy, m->data, DATASIZE);
    dataCopy[DATASIZE] = '\0'; // Ensure it's null-terminated

    // Find the first string within DATASIZE
    char *firstString = strtok(dataCopy, "()");

    // Find the second string within DATASIZE
    char *secondString = strtok(NULL, "()");

    // Convert the first string to uppercase
    for (int i = 0; firstString[i]; i++) {
        firstString[i] = toupper(firstString[i]);
    }

    // Convert the second string to lowercase
    for (int i = 0; secondString[i]; i++) {
        secondString[i] = tolower(secondString[i]);
    }

    // Copy the converted strings back to their respective positions in data
    memset(m->data, 0, DATASIZE);
    snprintf(m->data, DATASIZE, "%s()%s()", firstString, secondString);
}
