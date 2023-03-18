#include "client-step3.race.h"

int main()
{
    for (size_t task_counter = 0; task_counter < NUM_CONNECTIONS; task_counter += 1)
    {
        pthread_t thread;

        if (pthread_create(&thread, NULL, talk_to_server, (void*)&task_counter) != 0)
        {
            perror("Error: failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    sleep(5);

    return EXIT_SUCCESS;
}

void* talk_to_server(void* _send)
{
    // data
    int send = *((int*)_send);
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

    bytes_read = read(sock, &rec, sizeof(int));
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
