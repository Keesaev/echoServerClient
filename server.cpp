#include "server.h"

Server::Server(boost::asio::io_service *io_service, boost::mutex *outputMutex, unsigned short port) :
    io_service(io_service), outputMutex(outputMutex), port(port)
{
    acceptor = new ip::tcp::acceptor
            (*io_service, ip::tcp::endpoint(ip::tcp::v4(), port));
}

void Server::listen(){

    char buf[1024];
    boost::system::error_code errorCode;

    while( true ){
        ip::tcp::socket socket(*io_service);
        acceptor->accept(socket);
        socket.read_some(boost::asio::buffer(buf), errorCode);

        outputMutex->lock();
        std::cout << "Server reads: ";
        printf(buf);
        std::cout << std::endl;
        outputMutex->unlock();

        socket.write_some(boost::asio::buffer(buf), errorCode);

        socket.close();
    }
}

