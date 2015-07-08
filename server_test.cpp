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

TEST(StartStop, Creation) {
    Server server(50000);
    server.make_thread();
}



