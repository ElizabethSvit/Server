//
//  server.h
//  HttpServer
//
//  Created by Elizaveta on 06.07.15.
//  Copyright (c) 2015 Elizaveta. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <atomic> // use std::atomic<bool> run;
#include <thread>
#include <poll.h>

#define ERROR -1
#define MAXLINE 1024

#ifndef HttpServer_server_h
#define HttpServer_server_h

class Server {
private:

    int sockfd, client_sockfd;
    struct sockaddr_in server;
    char buff[MAXLINE];
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
    int buff_len;

    struct pollfd fds[1];
    std::atomic<bool> run;
    
public:
    Server() : run(true) {}
    Server(int port) {}

    void create_socket() {
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
            perror("server: can't open stream socket");
            exit(-1);
        }

        server.sin_family = AF_INET;
        // server.sin_port = htons(atoi(argv[1]));
        server.sin_port = htons(50000);
        server.sin_addr.s_addr = INADDR_ANY;
        bzero(&server.sin_zero, 8);
    }

    void bind_and_listen() {
        if ((bind(sockfd, (struct sockaddr *)&server, sockaddr_len)) == ERROR) {
            perror("server: can't bind local address");
            exit(-1);
        }
        listen(sockfd, 5);
    }

    void start() {
        while (true) {
            std::thread t(&Server::run, this);
            int flag = poll(fds, 1, 50);
            if(flag == 1) {
                client_sockfd = accept(sockfd, (struct sockaddr*) NULL, NULL);
                if (client_sockfd == ERROR) {
                    perror("server: can't accept");
                    exit(-1);
                }
            }
        }
    }
    void stop() {
        run = false;
        t.join();
    }

    void make_thread() {
        start();
        usleep(100000);
        stop();
    }

    void make_echo() {
        buff_len = 1;
        while (buff_len != 0) {
            buff_len = read(client_sockfd, buff, MAXLINE);
            write(client_sockfd, buff, buff_len);
        }
        printf("Client disconnected\n");
        close(client_sockfd);
    }
};


#endif


