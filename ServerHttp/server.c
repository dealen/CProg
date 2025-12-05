#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <pthread.h>

#include "utils/utils.h"
#include "modules/http.h"
#include "modules/router.h"

// Function which runs the thread (equivalent to Task.Run)
// takes in void* and return void*
void* handle_client(void *client_socket_pointer) {
    int client_socket = *((int*)client_socket_pointer);
    free(client_socket_pointer); // releasing allocated memory in method main

    printf("[Thread %lu] Processing client 's request %d\n", pthread_self(), client_socket);

    // for simulation of some long running process
    sleep(5);

    char buffer[4096] = {0};
    ssize_t bytes = read(client_socket, buffer, sizeof(buffer) - 1);

    if (bytes > 0) {
        // ignoring content of the request, just resposning
        const char *body = "Hello from Thread!";
        char response[1024];

        int len = snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %ld\r\n"
            "\r\n"
            "%s",
            strlen(body), body
        );

        write(client_socket, response, len);
    }

    close(client_socket);
    printf("[Thread %lu] End of processing clients request %d\n", pthread_self(), client_socket);

    return NULL;
}

int main()
{
    // socket creation
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
    {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // configuring address
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    // binding to port
    if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    // listening...
    if (listen(server, 10) < 0)
    {
        perror("listen");
        return 1;
    }

    print_time();
    printf("Server working on http://localhost:8080\n");
    printf("Press Ctrl+C to terminate\n\n");
    fflush(stdout);

    int request_num = 0;

    while (1)
    {
        request_num++;

        print_time();
        printf("[%d] Waiting for requests...\n", request_num);
        fflush(stdout);

        // checking for any client requests
        int client = accept(server, NULL, NULL);
        if (client < 0)
        {
            perror("accept");
            continue;
        }

        printf("[Main] new connection, creating new thread.");

        int *pclient = malloc(sizeof(int));
        *pclient = client;

        pthread_t thread_id;

        if (pthread_create(&thread_id, NULL, handle_client, pclient) != 0) {
            perror("pthread_create");
            free(pclient);
            close(client);
        } else {
            // detach = fire & forget
            // we are not going to wait for this thread, system will clean up on its own
            pthread_detach(thread_id);
        }

    }

    close(server);
    return 0;
}
