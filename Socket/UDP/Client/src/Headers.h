/*
 * Headers.h
 *
 *  Created on: 22 nov 2023
 *  Author: Leonardo Birardi
 */

#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

#if defined WIN32
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define closesocket close
#endif

#endif /* HEADERS_H_ */
