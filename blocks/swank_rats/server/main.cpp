//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include "diego/zmqcpp/zmq.hpp"
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif

int main () {
    const char *bind_to = "tcp://127.0.0.1:5555";

    int rc;

    void *ctx = zmq_init(1);

    void *s_in = zmq_socket(ctx, ZMQ_PULL);

    int conflate = 1;
    rc = zmq_setsockopt(s_in, ZMQ_CONFLATE, &conflate, sizeof(conflate));

    rc = zmq_bind(s_in, bind_to);

    void *s_out = zmq_socket(ctx, ZMQ_PUSH);

    rc = zmq_connect(s_out, bind_to);

    int message_count = 100;
    for (int j = 0; j < message_count; ++j) {
        rc = zmq_send(s_out, (void *) &j, sizeof(int), 0);
        std::cout << "send: " << j << std::endl;

        if (rc < 0) {
            printf("error in zmq_sendmsg: %s\n", zmq_strerror(errno));
            return -1;
        }

        zmq_sleep(1);
    }
}