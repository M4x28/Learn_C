/*
 * Server.h
 *
 *  Created on: November 6, 2023
 *  Author: Leonardo Birardi
 */

#ifndef SERVER_H_
#define SERVER_H_

// Define the server port and buffer size constants
#define PROTOPORT 57015
#define BUFFERSIZE 512

// Define the maximum queue size for pending client connections
#define QUEUE 6

// Define a constant for no error
#define NO_ERROR 0

// Define maximum sizes for data, operator, and option fields in the message structure
#define DATASIZE 410
#define OPERATORSIZE 51
#define OPTIONSIZE 51

// Define a structure to hold the message data
typedef struct {
    char data[DATASIZE];     // Data field to store information
    char operator[OPERATORSIZE]; // Operator field for operations (optional)
    char option[OPTIONSIZE];     // Option field for additional information (optional)
} msg;

#endif /* SERVER_H_ */
