#ifndef SERVER_H_
#define SERVER_H_

#include <arl/math/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// http://www.linuxhowtos.org/C_C++/socket.htm
// https://stackoverflow.com/questions/26043744/access-class-variable-from-stdthread

#include "communication/rx_list.h"

namespace plot_tool
{
class Server
{
private:
    int sockfd_;
    int newsockfd_;
    bool client_connected_;
    size_t max_elements_;

    struct sockaddr_un cli_addr_;
    socklen_t clilen_;

    std::vector<char*> receive_buffer_pointers_;
    std::string socket_name_;
    std::vector<std::string>* qt_commands_;

    plot_tool::RxList& rx_list_internal_;

    std::mutex* mtx_;
    void receiveThread();

    void receiveInternal();
    void receiveData(const RxList& rx_list);

public:
    char* getBufferPointer(const size_t idx);
    size_t getNumBufferPointers() const;
    void start();
    void receive();
    void connect();
    Server() = delete;
    Server(const std::string& socket_name,
           const size_t num_buffer_elements,
           std::mutex* mtx,
           std::vector<std::string>* qt_commands,
           plot_tool::RxList& rx_list);
    ~Server();
    bool clientConnected();
};

}  // namespace plot_tool

#endif
