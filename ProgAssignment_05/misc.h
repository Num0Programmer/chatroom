//
//  misc.h
//
//  Created by Wolf-Dieter Otte on 3/15/23.
//


#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>


// converts unsigned int representation of IP to dotted string representation
char* ip_ntop(unsigned int ip);

// converts dotted string representation of IP to unsigned int representation
unsigned int ip_pton(char* ip_string);

// read from a socket a number of bytes, only returns after all bytes read
int read_complete(int socket, void* buffer, unsigned int size);

// checks if string starts with a given prefix
bool starts_with(const char *string, const char *prefix);

#endif /* util_h */
