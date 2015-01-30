#include "diego/zmqcpp/zmq.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

int main() {
    const char *bind_to = "tcp://127.0.0.1:5555";

    int rc;

    void *ctx = zmq_init(1);
    //assert(ctx);

    void *s_in = zmq_socket(ctx, ZMQ_PULL);
    //assert(s_in);

    int conflate = 1;
    rc = zmq_setsockopt(s_in, ZMQ_CONFLATE, &conflate, sizeof(conflate));
    //assert(rc == 0);

    rc = zmq_bind(s_in, bind_to);
    //assert(rc == 0);

    void *s_out = zmq_socket(ctx, ZMQ_PUSH);
    //assert(s_out);

    rc = zmq_connect(s_out, bind_to);
    //assert(rc == 0);

    int message_count = 20;
    for (int j = 0; j < message_count; ++j) {
        rc = zmq_send(s_out, (void *) &j, sizeof(int), 0);
        std::cout << j << std::endl;
        if (rc < 0) {
            printf("error in zmq_sendmsg: %s\n", zmq_strerror(errno));
            return -1;
        }
    }
    zmq_sleep(1);

    int payload_recved = 0;
    rc = zmq_recv(s_in, (void *) &payload_recved, sizeof(int), 0);
    //assert(rc > 0);
    //assert(payload_recved == message_count - 1);

    std::cout << payload_recved << std::endl;

    rc = zmq_close(s_in);
    //assert(rc == 0);

    rc = zmq_close(s_out);
    //assert(rc == 0);

    rc = zmq_term(ctx);
    //assert(rc == 0);

    return 0;
}