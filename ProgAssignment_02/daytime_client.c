#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    struct hostent *host_entry;         // host information struct
    char msg[MSG_SIZE];                 // message buffer
    
    host_entry = gethostbyname(NIST_IP);
    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // create addr struct
    client_address.sin_family = AF_INET;
    //inet_aton(host_entry->h_addr_list[0], &client_address.sin_addr);
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);
    
    // connect to server socket
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1)
    {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }

    // store message from time.nist.gov
    read(client_socket, &msg, sizeof(char) * MSG_SIZE);

    // print received message
    if (msg[0] != '\0')
    {
        
        int i = 0;
        while (msg[i] != '\0')
        {
            printf("%c", msg[i]);
            i += 1;
        }
    }
    // assume nothing came
    else
    {
        printf("No message recieved!\n");
    }

    close(client_socket);

    return EXIT_SUCCESS;
}
