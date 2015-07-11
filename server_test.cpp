//
//  server_test.cpp
//  HttpServer
//
//  Created by Elizaveta on 06.07.15.
//  Copyright (c) 2015 Elizaveta. All rights reserved.
//

#include "gtest/gtest.h"
#include "server.h"
#include <thread>
#include <string.h>

TEST(Server, Creation) {
    int a = 1;
    int b = a;
    ASSERT_EQ(a, b);
}

/*TEST(ServerClass, Creation) {
    Server server(50000);
    server.start();
    server.stop();
}*/

void TestThread() {
    std::cerr << "b" << std::endl;
    usleep(200000);
    std::cerr << "d" << std::endl;
}

TEST(Tread, Creation) {
    std::cerr << "a" << std::endl;
    std::thread t2(TestThread);
    usleep(100000);
    std::cerr << "c" << std::endl;
    t2.join();
}

TEST(StartStop, SingleConnection) {
    Server server(50000);
    server.start(make_echo);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(50000);
    bzero(&servaddr, sizeof(servaddr));
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    write(sockfd, "hello", 5);
    std::string buff;
    read(sockfd, &buff, 1024);
    // std::string read_str;

    /*if (buff == "hello") {
        printf("OK");
    } else {
        printf("NOT OK");
    }*/

    // create socket()
    // connect() to server
    // send request
    // check response

    sleep(2);

    server.stop();
}



