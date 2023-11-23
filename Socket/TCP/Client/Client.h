/*
 * Client.h
 *
 *  Created on: November 6, 2023
 *  Author: Leonardo Birardi
 */

#ifndef CLIENT_H_
#define CLIENT_H_

// Define constants for buffer size and server port
#define BUFFERSIZE 512
#define PROTOPORT 57015

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

#endif /* CLIENT_H_ */
