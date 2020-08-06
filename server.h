#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>

using namespace boost::asio;
using namespace std;

class Server
{
public:
    Server(io_service *io_service, boost::mutex *outputMutex, unsigned short port);
    ~Server(){
        delete acceptor;
    }
    void listen();
private:
    io_service *io_service;
    boost::mutex *outputMutex;
    ip::tcp::acceptor *acceptor;

    unsigned short port;
    std::string ip = "127.0.0.1";
};

#endif // SERVER_H
