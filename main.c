// Simple HTTP Webserver
// Used guide: https://www.beej.us/guide/bgnet/pdf/bgnet_a4_c_2.pdf

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "callback.h"
#include "router.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "12000"
#define MAX_INCOMING_REQUESTS 5

void test(char **args);
void test1(char **args);

Router init_routes(void) {
    Router router = create_router();
    
    add_route(router, "hello", test, GET);
    add_route(router, "hello", test1, POST);
    add_route(router, "ok", test, DELETE);
    add_route(router, "melon", test1, PUT);
    
    return router;
}

int main(void) {
    Router router = init_routes();

    struct addrinfo hints;
    struct addrinfo *servinfo;          // will point to the results
    memset(&hints, 0, sizeof hints);    // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;        // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;        // fill in my IP for me

    int status;
    if ((status = getaddrinfo(NULL, SERVER_PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // Create welcome socket file descriptor
    int welcome_sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol); 
    if (welcome_sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Set socket to reuse address/port 
    int yes = 1;
    if (setsockopt(welcome_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
        perror("setsockopt");
        exit(1);
    }
    if (setsockopt(welcome_sockfd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes)) < 0) {
        perror("setsockopt");
        exit(1);
    }
    
    // bind socket to port we passed into getaddrinfo()
    if (bind(welcome_sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
        perror("bind");
        exit(1);
    } 

    // Set socket to listen to requests
    if (listen(welcome_sockfd, MAX_INCOMING_REQUESTS)) {
        perror("listen");
        exit(1);
    }

    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof client_addr;
    int client_sockfd;
    if ((client_sockfd = accept(welcome_sockfd, (struct sockaddr *)&client_addr, &client_addr_size)) < 0) {
        perror("accept");
        exit(1);
    }

    char *msg = "Hello world";
    int len = strlen(msg);
    int bytes_sent = send(client_sockfd, msg, len, 0);
    


    freeaddrinfo(servinfo);
    return 0;
}

void test(char **args) {
    printf("Hello world\n");
}

void test1(char **args) {
    printf("Hello Cool\n");
}