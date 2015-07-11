#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
<<<<<<< HEAD
#include "server.h"
=======
>>>>>>> a31c3c50e524ac801828242bae5454be043a4f9d

#define ERROR -1
#define MAXLINE 1024

int main(int argc, char **argv) {
<<<<<<< HEAD
    /*
    int sockfd, client_sockfd;
    struct sockaddr_in server;
    char buff[MAXLINE];
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
=======
>>>>>>> a31c3c50e524ac801828242bae5454be043a4f9d
    int sockfd, client_sockfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buff[MAXLINE];
    int sockaddr_len = sizeof(struct sockaddr_in);
    int buff_len;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        perror("server: can't open stream socket");
        exit(-1);
    }

    server.sin_family = AF_INET;
<<<<<<< HEAD
    // server.sin_port = htons(atoi(argv[1]));
    server.sin_port = htons(50000);
=======
>>>>>>> a31c3c50e524ac801828242bae5454be043a4f9d
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    if ((bind(sockfd, (struct sockaddr *)&server, sockaddr_len)) == ERROR) {
        perror("server: can't bind local address");
        exit(-1);
    }
    listen(sockfd, 5);

    while (true) {
<<<<<<< HEAD
        client_sockfd = accept(sockfd, (struct sockaddr*) NULL, NULL);
        // client_sockfd = accept(sockfd, (struct sockaddr*)&client, &sockaddr_len);
=======
>>>>>>> a31c3c50e524ac801828242bae5454be043a4f9d

        client_sockfd = accept(sockfd, (struct sockaddr*) NULL, NULL);
        if (client_sockfd == ERROR) {
            perror("server: can't accept");
            exit(-1);
        }
<<<<<<< HEAD
=======

>>>>>>> a31c3c50e524ac801828242bae5454be043a4f9d
        printf("New client connected with port number %d and IP %s\n", ntohs(client.sin_port),
               inet_ntoa(client.sin_addr));

        buff_len = 1;
        while (buff_len != 0) {
            buff_len = read(client_sockfd, buff, MAXLINE);
            write(client_sockfd, buff, buff_len);
        }
        printf("Client disconnected\n");
        close(client_sockfd);
    }
<<<<<<< HEAD
     */
    
    Server s(50000);
//    s.start();

    while(true) { sleep(10); }

    return 0;
=======

>>>>>>> a31c3c50e524ac801828242bae5454be043a4f9d
}

