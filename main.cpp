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

    unsigned short port = 8001; // Random port

    Server *serv = new Server(&io_service_server, &outputMutex, port);
    boost::thread serverThread(&Server::listen, serv);

    std::vector<Client*> clients;
    std::vector<boost::thread> threads;

    for(int i = 0; i < 5; i++){
        clients.push_back(new Client(&io_service_client,
                                     &outputMutex,
                                     std::to_string(i + 1),
                                     port));
        threads.push_back(boost::thread{&Client::write, clients[i]});
        //threads[i].join(); // Thread executing one by one
    }

    // Threads executing in random order

    for(int i = 0; i < 5; i++)
        threads[i].join();

    serverThread.join();

    return a.exec();
}
