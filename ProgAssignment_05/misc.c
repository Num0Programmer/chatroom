//
//  misc.c
//
//  Created by Wolf-Dieter Otte on 3/15/23.
//


#include "misc.h"


// converts unsigned int representation of IP to dotted string representation
char* ip_ntop(unsigned int ip)
{
    struct sockaddr_in sa;
    char* ip4_string;
    
    sa.sin_addr.s_addr = ip;
    ip4_string = (char*) malloc(INET_ADDRSTRLEN);

    inet_ntop(AF_INET, &ip, ip4_string, INET_ADDRSTRLEN);

    return ip4_string;
}


// converts dotted string representation of IP to unsigned int representation
unsigned int ip_pton(char* ip_string)
{
    struct sockaddr_in sa;

    inet_pton(AF_INET, ip_string, &(sa.sin_addr));
    
    return (unsigned int) sa.sin_addr.s_addr;
}


// read from a socket a number of bytes, only returns after all bytes read
int read_complete(int socket, void* buffer, unsigned int size)
{
    ssize_t bytes_read = 0;
    ssize_t bytes_read_all = 0;
    char* buffer_ptr = buffer;
    
    do
    {
        bytes_read = read(socket, buffer_ptr, size);
        
        switch(bytes_read)
        {
            //case 0:
                // end of file
                //return 0;
            case -1:
                // network error
                return -1;
            default:
                size = size - (int)bytes_read;
                buffer_ptr += bytes_read;
                bytes_read_all += bytes_read;
        }        
    }
    while(size != 0);
    
    return (int) bytes_read_all;
}


// low-level implementation of prefix string matching
bool starts_with(const char *string, const char *prefix)
{
    while(*prefix)
    {
        if(*prefix++ != *string++)
        {
            return false;
        }
    }

    return true;
}
