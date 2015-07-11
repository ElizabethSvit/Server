#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "server.h"

int main(int argc, char **argv) {

    Server s(50000);
    // s.start();

    while(true) { sleep(10); }

    return 0;
}

