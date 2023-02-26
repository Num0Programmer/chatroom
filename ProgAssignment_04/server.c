#include "server.h"


/* ************************************************************************* */
/* MAIN                                                                      */
/* ************************************************************************* */

int main(int argc, char** argv) {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket

    // sent when client disconnected
    signal(SIGPIPE, SIG_IGN);
    
    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on
    
    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    
    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) != 0) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }
    
    // server loop
    while (TRUE) {
        
        // accept connection to client
        int client_socket = accept(server_socket, NULL, NULL);
        printf("\nServer with PID %d: accepted client\n", getpid());

        // create thread to handle the client's request
        // note that this is a naive approach, i.e. there are race conditions
        // for now this is okay, assuming low load
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
        
        // detach the thread so that we don't have to wait (join) with it to reclaim memory.
        // memory will be reclaimed when the thread finishes.
        if (pthread_detach(thread) != 0) {
            perror("Error detaching thread");
            exit(EXIT_FAILURE);
        }
    }
}


/* ************************************************************************* */
/* handle client                                                             */
/* ************************************************************************* */

void* handle_client(void* arg) { // xxxxx
    int client_socket = *((int*)arg);   // the socket connected to the client
    int input;
    int collatz_num;
    int keep_going = TRUE;
    
    while (keep_going) {
        // read char from client
        switch (read(client_socket, &input, sizeof(int))) {
            case 0:
                keep_going = FALSE;
                perror("End of stream, returning ...\n");
                break;
            case -1:
                perror("Error reading from network!\n");
                keep_going = FALSE;
                break;
        }
        printf("%d", input);
        
        // check if we terminate
        if (input == 'q') {
            keep_going = FALSE;
        }


        collatz_num = collatz_conj(input);

        // send result back to client
        write(client_socket, &collatz_num, sizeof(int));
    }
    
    // cleanup
    if (close(client_socket) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    } else {
        printf("Closed socket to client, exit");
    }
    
    pthread_exit(NULL);
}

int collatz_conj(int num)
{
        // initialize variables
        int steps = 0;
        
        // loop while number is not 1
        while (num != 1)
        {
            // check if int_num is odd
            if (num % 2 != 0)
            {
                // set int_num equal to (3 * int_num) + 1
                num = (3 * num) + 1;
            }
            // otherwise it's even
            else
            {
                // set int_num equal to int_num/2
                num /= 2;
            }   
            // increment steps 
            steps += 1;
        }
        
        // return steps
        return steps;
}