#include "client-step2.complete-reads.h"

int main()
{
    for (size_t thread_num = 0; thread_num < NUM_CONNECTIONS; thread_num += 1)
    {
        pthread_t thread;

        if (pthread_create(&thread, NULL, talk_to_server, NULL) != 0)
        {
            perror("Error: failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    sleep(5);

    return EXIT_SUCCESS;
}

int read_int(int socket, int* int_value_ptr)
{
    int bytes_read;

    for (int bytes_left = 4; bytes_left > 0; bytes_left -= bytes_read)
    {
        bytes_read = read(socket, int_value_ptr, sizeof(int));

        if (bytes_read == 4)
        {
            break;  // all bytes read in one go
        }
        else if (bytes_read == -1)
        {
            break;  // problem in network
        }

        *int_value_ptr <<= (bytes_left - bytes_read) * 8;
    }

    return 4;
}

void* talk_to_server()
{
    // data
    int send = 7;
    int rec;
    int bytes_read = -1;

    // networking information
    int sock;
    struct sockaddr_in client_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(HOME_ADDR);
    client_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
    {
        printf("Error: connection unsuccessful!\n");
        exit(EXIT_FAILURE);
    }

    printf("Sending: %d\n", send);
    send = htonl(send);
    write(sock, &send, sizeof(int));

    bytes_read = read_int(sock, &rec);
    rec = ntohl(rec);
    printf("Number of iterations: %d\n", rec);
    if (bytes_read < 4)
    {
        printf("%d bytes were read!\n", bytes_read);
    }

    // exit function
    close(sock);
    pthread_exit(NULL);
}
