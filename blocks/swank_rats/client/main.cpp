//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include "diego/zmqcpp/zmq.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

int main() {
    const char *bind_to = "tcp://127.0.0.1:5555";

    int rc;

    void *ctx = zmq_init(1);

    void *s_in = zmq_socket(ctx, ZMQ_PULL);

    int conflate = 1;
    rc = zmq_setsockopt(s_in, ZMQ_CONFLATE, &conflate, sizeof(conflate));

    rc = zmq_bind(s_in, bind_to);

    while (1) {
        int payload_recved = 0;
        rc = zmq_recv(s_in, (void *) &payload_recved, sizeof(int), 0);

        std::cout << "received: " << payload_recved << std::endl;

        zmq_sleep(5);
    }
}
