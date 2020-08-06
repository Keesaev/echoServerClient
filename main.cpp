#include <QCoreApplication>
#include <client.h>
#include <server.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    boost::asio::io_service io_service_client;
    boost::asio::io_service io_service_server;
    boost::mutex outputMutex; // Used to synchronise console output

    unsigned short port = 8001;

    Server *serv = new Server(&io_service_server, &outputMutex, port);
    Client *cl = new Client(&io_service_client, &outputMutex, "One", port);

    boost::thread serverThread(&Server::listen, serv);
    boost::thread clientThread{&Client::write, cl};

    serverThread.join();
    clientThread.join();

    return a.exec();
}
