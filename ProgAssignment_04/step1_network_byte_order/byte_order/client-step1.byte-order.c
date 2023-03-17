#include "client-step1.byte-order.h"

int main()
{
    // networking information
    int sock;
    struct sockaddr_in client_addr;

    // data
    int input;
    int rec;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(HOME_ADDR);
    client_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
    {
        printf("Error: connection unsuccessful!\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter a number: ");
    scanf("%d", &input);
    printf("\n");

    input = htonl(input);
    write(sock, &input, sizeof(int));

    read(sock, &rec, sizeof(int));
    rec = ntohl(rec);
    printf("Number of iterations: %d\n", rec);

    close(sock);

    return EXIT_SUCCESS;
}

