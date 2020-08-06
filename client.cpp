#include "client.h"

Client::Client(boost::asio::io_service *io_service, boost::mutex *outputMutex,
               std::string name, unsigned short port) :
            io_service(io_service),
            outputMutex(outputMutex),
            name(name),
            port(port)
{
    ep = new ip::tcp::endpoint(ip::address::from_string(ip), port);
    socket = new ip::tcp::socket(*io_service);
}

bool Client::write(){

    // Connect

    try {
        socket->connect(*ep);
    }
    catch (std::exception& e) {
        std::cerr << "Client " << name << " error: " << e.what() << std::endl;
        return 0;
    }

    // Declarations

    char buf[1024];
    boost::system::error_code errorCode;
    char msg[1024];
    strcpy(msg, "Client ");
    strcat(msg, name.data());
    strcat(msg, " message");
    size_t length = 1;

    // Send data

    socket->write_some(boost::asio::buffer(msg));

    // Read data

    try{
        while(true){
            length = socket->read_some(boost::asio::buffer(buf), errorCode);

            if(errorCode == boost::asio::error::eof){ // End of file
                socket->close();
                break;
            }
            else if(errorCode)                       // Other errors
                throw(boost::system::system_error(errorCode));

            outputMutex->lock();
            std::cout << "Client " << name << " reads: ";
            printf(buf);
            std::cout << std::endl;
            outputMutex->unlock();

        }
    }
    catch(boost::system::system_error& e){
        std::cerr << "Client " << name << " error: " << e.what() << std::endl;
        return 0;
    }

    outputMutex->lock();
    std::cout << "Client " << name << " is not active\n";
    outputMutex->unlock();

    return 1;
}

