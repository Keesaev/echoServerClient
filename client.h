#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>

using namespace boost::asio;

class Client
{
public:
    Client(io_service *io_service, boost::mutex *outputMutex, std::string name, unsigned short port);
    ~Client(){
        socket->close();
        delete socket;
    }
    bool write();
private:

    io_service *io_service;
    boost::mutex *outputMutex;
    ip::tcp::endpoint *ep;
    ip::tcp::socket *socket;

    std::string ip = "127.0.0.1";
    std::string name;
    unsigned short port;
};

#endif // CLIENT_H
