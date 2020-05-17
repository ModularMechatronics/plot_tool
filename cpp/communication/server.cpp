#include "communication/server.h"

#include <arl/utilities/logging.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <csignal>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "communication/rx_list.h"
#include "communication/socket_communication_utilities.h"

// https://developer.ibm.com/tutorials/l-sockpit/

namespace plot_tool
{
void Server::receiveData(const RxList& rx_list)
{
    const bool has_payload = rx_list.getObjectData<HasPayloadRx>();
    sendAck(newsockfd_);

    if (has_payload)
    {
        const size_t num_buffers_required = rx_list.getObjectData<NumBuffersRequiredRx>();
        const size_t num_bytes = rx_list.getObjectData<NumBytesRx>();

        for (size_t k = 0; k < num_buffers_required; k++)
        {
            receiveArbLenData(receive_buffer_pointers_[k], newsockfd_, num_bytes, max_elements_);
        }
    }

    rx_list_internal_.copy(rx_list);
}

void Server::receiveInternal()
{
    RxList rx_list = receiveRxList(newsockfd_);

    if (rx_list.isEmpty())
    {
        client_connected_ = false;
    }
    else
    {
        receiveData(rx_list);
    }
}

char* Server::getBufferPointer(const size_t idx)
{
    ASSERT(idx < 6) << "Index too big! Must be smaller than 6!";

    return receive_buffer_pointers_[idx];
}

size_t Server::getNumBufferPointers() const
{
    return receive_buffer_pointers_.size();
}

void Server::receive()
{
    if (!client_connected_)
    {
        std::cout << "Client disconnected..." << std::endl;
        newsockfd_ = accept(sockfd_, (struct sockaddr*)&cli_addr_, &clilen_);
        client_connected_ = true;
    }

    receiveInternal();
}

void Server::start()
{
    struct sockaddr_un serv_addr;

    if ((sockfd_ = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        LOG_ERROR() << "Error creating socket!";
        exit(-1);
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;

    std::string socket_name_extended = "/tmp/" + socket_name_;
    strcpy(serv_addr.sun_path, socket_name_extended.c_str());

    const int servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    int bind_success = bind(sockfd_, (struct sockaddr*)&serv_addr, servlen);
    if (bind_success < 0)
    {
        LOG_ERROR() << "Error binding socket!";
        exit(-1);
    }

    listen(sockfd_, 5);
    int flag = 1;
    setsockopt(sockfd_, 6, TCP_NODELAY, (char*)&flag, sizeof(int));

    // Initialize socket
    clilen_ = sizeof(cli_addr_);
    newsockfd_ = accept(sockfd_, (struct sockaddr*)&cli_addr_, &clilen_);
    std::cout << "Connection accepted" << std::endl;

    flag = 1;
    setsockopt(newsockfd_, 6, TCP_NODELAY, (char*)&flag, sizeof(int));

    if (newsockfd_ < 0)
    {
        LOG_ERROR() << "Error accepting socket!";
        exit(-1);
    }

    client_connected_ = true;
}

bool Server::clientConnected()
{
    return client_connected_;
}

void Server::connect()
{
    newsockfd_ = accept(sockfd_, (struct sockaddr*)&cli_addr_, &clilen_);
    client_connected_ = true;
}

Server::~Server()
{
    close(sockfd_);

    for (size_t k = 0; k < receive_buffer_pointers_.size(); k++)
    {
        delete[] receive_buffer_pointers_[k];
    }
}

Server::Server(const std::string& socket_name,
               const size_t num_buffer_elements,
               std::mutex* mtx,
               std::vector<std::string>* qt_commands,
               RxList& rx_list)
    : client_connected_(false), rx_list_internal_(rx_list)
{
    mtx_ = mtx;
    qt_commands_ = qt_commands;
    socket_name_ = socket_name;

    max_elements_ = 2000;

    // Allocate elements for the receive buffer
    const size_t num_buffer_pointers = 6;
    for (size_t k = 0; k < num_buffer_pointers; k++)
    {
        char* buffer_pointer = new char[num_buffer_elements];
        receive_buffer_pointers_.push_back(buffer_pointer);
    }
}

}  // namespace plot_tool
