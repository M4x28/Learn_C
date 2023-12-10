/*
 * Server.h
 *
 *  Server Header file
 *  Created on: November 9, 2023
 *  Author: Leonardo Birardi
 */

#ifndef SERVER_H_
#define SERVER_H_

#define PROTOPORT 56700  		// Default Server Port
#define PROTO_ADDR "127.0.0.1"  // Default Server Address
#define BUFFERSIZE 256  		// Default Buffer Size

								// Define the maximum queue size for pending client connections
#define QUEUE 5

#define MAXOPERANDS 2 			// Maximum number of operands

char msg[BUFFERSIZE]; 			// Message Array

#endif /* SERVER_H_ */
