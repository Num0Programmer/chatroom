#include "server.h"


/* ************************************************************************* */
/* MAIN                                                                      */
/* ************************************************************************* */
int main() {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket

    // sent when client disconnected
    signal(SIGPIPE, SIG_IGN);
    
    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on
    
    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    
    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) != 0)
    {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    // give prelim information about server
    printf("Server started - listening on port: %d\n", PORT);
    
    // server loop
    while (TRUE)
    {    
        // accept connection to client
        int client_socket = accept(server_socket, NULL, NULL);
        printf("\nServer with PID %d: accepted client\n", getpid());

        // create thread to handle the client's request
        // note that this is a naive approach, i.e. there are race conditions
        // for now this is okay, assuming low load
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0)
        {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
        
        // detach the thread so that we don't have to wait (join) with it to reclaim memory.
        // memory will be reclaimed when the thread finishes.
        if (pthread_detach(thread) != 0)
        {
            perror("Error detaching thread");
            exit(EXIT_FAILURE);
        }
    }
}


/* ************************************************************************* */
/* handle client                                                             */
/* ************************************************************************* */

void* handle_client(void* arg)
{
    int index = 0;
    int client_socket = *((int*)arg);   // the socket connected to the client 
    char msg[MSG_SIZE];
    int nist_socket;
    struct sockaddr_in client_address;  // for naming the client socket
    struct hostent *host_entry;         // naming the host socket

    host_entry = gethostbyname(NIST_IP); // ask otte

    nist_socket = socket(AF_INET, SOCK_STREAM, 0);
    // setup client side
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(NIST_IP);
    client_address.sin_port = htons(NIST_PORT);

    if (connect(nist_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1)
    {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }

    // grab time message from time.nist.gov
    read(nist_socket, &msg, sizeof(char) * MSG_SIZE);

    // send time to client
    write(client_socket, msg, sizeof(char) * MSG_SIZE);
        
    // cleanup
    if (close(client_socket) == -1)
    {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Closed socket to client, exit\n");
    }

    close(nist_socket);
    
    pthread_exit(NULL);
}

/************************************************************************** */
/* send time                                                                */
/************************************************************************** */
void send_time(int client_socket)
{
//    char input[MSG_SIZE];

//   sprintf(input, "%d-%d-%d %s:%s:%s", tm_year - 1900, tm_mon + 1, tm_mday, "0", "0", "0");

//    write(client_socket, ctime(&cur_secs), sizeof(char));
}

