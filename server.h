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
#include <functional>
#include <poll.h>

#define ERROR -1
#define MAXLINE 1024

#ifndef HttpServer_server_h
#define HttpServer_server_h

class Server {
private:
    int sockfd_;
    int port_;
    std::atomic<bool> run_;
    std::thread t_;

    void accept_loop(std::function<void(int)> handler) {
        struct pollfd fds[1];

        while (run_) {
            int flag = poll(fds, 1, 50);
            if(flag == 1) {
                int client_sockfd = accept(sockfd_, (struct sockaddr*) NULL, NULL);
                if (client_sockfd == ERROR) {
                    perror("server: can't accept");
                    exit(-1);
                }

                handler(client_sockfd);
            }
        }
    }

public:
    Server(int port) : port_(port), run_(true) {}

    void start(std::function<void(int)> handler) {
        struct sockaddr_in server;
        socklen_t sockaddr_len = sizeof(struct sockaddr_in);

        if ((sockfd_ = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
            perror("server: can't open stream socket");
            exit(-1);
        }

        server.sin_family = AF_INET;
        // server.sin_port = htons(atoi(argv[1]));
        server.sin_port = htons(50000);
        server.sin_addr.s_addr = INADDR_ANY;
        bzero(&server.sin_zero, 8);

        if ((bind(sockfd_, (struct sockaddr *)&server, sockaddr_len)) == ERROR) {
            perror("server: can't bind local address");
            exit(-1);
        }
        listen(sockfd_, 5);

        t_ = std::thread(&Server::accept_loop, this, handler);
    }

    void stop() {
        run_ = false;
        t_.join();
    }
};

void make_echo(int client_sockfd) {
    int buff_len = 1;
    char buff[MAXLINE];

    while (buff_len != 0) {
        buff_len = read(client_sockfd, buff, MAXLINE);
        write(client_sockfd, buff, buff_len);
    }
    printf("Client disconnected\n");
    close(client_sockfd);
}

#endif


