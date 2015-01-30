//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include "diego/zmqcpp/zmq.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

int main () {
    int i=0;
    zmq::context_t context (1);
    zmq::socket_t subscriber (context, ZMQ_PULL);

    int conflate = 1;
    zmq_setsockopt (subscriber, ZMQ_CONFLATE, &conflate, sizeof(conflate));

    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    for (int update_nbr = 0; update_nbr < 100; update_nbr++)
    {
        zmq::message_t update;
        subscriber.recv(&update);
        i++;
        std::cout<<"receiving  :"<<i<<std::endl;

        usleep(10000000);
    }
}