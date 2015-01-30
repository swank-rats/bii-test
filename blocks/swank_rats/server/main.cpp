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
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUSH);
    publisher.bind("tcp://*:5556");

    int i = 0;
    for (int update_nbr = 0; update_nbr < 100; update_nbr++) {
        usleep(1000000);

        //  Send message to all subscribers
        zmq::message_t request(20);

        time_t seconds;
        seconds = time(NULL);

        char update[20] = "";
        sprintf(update, "%ld", seconds);

        memcpy((void *) request.data(), update, strlen(update));
        publisher.send(request);
        i++;
        std::cout << "sending :" << i << std::endl;
    }
}