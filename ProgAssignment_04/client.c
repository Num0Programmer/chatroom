#include "client.h"

// args that will be passed into pthread create
struct arg_struct
{
    int task_counter;
    pthread_mutex_t mutex;
};

int main()
{
    // networking information
    struct arg_struct *args;

    //Assign memory to the pointer
    args = malloc(sizeof(struct arg_struct));

    int number_of_tasks = 10;
    // init mutex with built in function
    pthread_mutex_init(&args->mutex, NULL);

    for (args->task_counter = 0; args->task_counter < number_of_tasks; args->task_counter+=1)
    {
        pthread_t thread;
        // allow only one thread to pass at a time
        pthread_mutex_lock(&args->mutex);

        if (pthread_create(&thread, NULL, talk_to_server, (void*)args))
        {
            printf("Creating thread failed\n");
            exit(EXIT_FAILURE);
        }

    }

    // delete the mutex
    pthread_mutex_destroy(&args->mutex);

    // free stuff
    free(args);

    return EXIT_SUCCESS;
}


void* talk_to_server(void *arguments)
{
    struct arg_struct *args = arguments;

    int number = args->task_counter;
    printf("task counter :%d\n", number);

    // unlock the mutex AKA let a thread 
    pthread_mutex_unlock(&args->mutex);

    // CAN BE UNCOMMNETED. Is commented out in order to see if mutiple threads were working
    /*
    struct sockaddr_in client_addr;
    int rec;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(HOME_ADDR);
    client_addr.sin_port = htons(HOME_PORT);


    if (connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
    {
        printf("Error: connection unsuccessful!\n");
        exit(EXIT_FAILURE);
    }

    write(sock, &number, sizeof(int));
    read(sock, &rec, sizeof(int));


    */
    printf("Number of iterations: %d\n", number);

    //close(sock);
}
