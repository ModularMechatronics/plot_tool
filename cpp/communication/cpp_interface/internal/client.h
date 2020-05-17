#ifndef CLIENT_H_
#define CLIENT_H_

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "image/image.h"
#include "internal/communication_functions.h"
#include "internal/communication_variables.h"
#include "math/math.h"

namespace plot_tool
{
constexpr size_t max_elements_ = 2000;

inline void initialize(const std::string& socket_name)
{
    if (!getClientIsInitialized())
    {
        const std::string socket_name_extended = "/tmp/" + socket_name;

        struct sockaddr_un server_addr;
        bzero((char*)&server_addr, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, socket_name_extended.c_str());

        const int server_obj_length = strlen(server_addr.sun_path) + sizeof(server_addr.sun_family);
        if ((_Var_client_socket_handle() = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        {
            std::cout << "Error creating socket!";
            exit(-1);
        }
        setClientSocketHandle(_Var_client_socket_handle());

        const int connection_successful =
            connect(getClientSocketHandle(), (struct sockaddr*)&server_addr, server_obj_length);

        if (connection_successful < 0)
        {
            std::cout << "Error connecting!";
            exit(-1);
        }

        int flag = 1;
        setsockopt(getClientSocketHandle(), 6, TCP_NODELAY, (char*)&flag, sizeof(int));
        setClientIsInitialized(true);
    }
}

inline void initialize()
{
    initialize("socket_file");
}

inline void deinitialize()
{
    close(_Var_client_socket_handle());
}

inline void sendData(const char* const buffer, const size_t num_bytes)
{
    writeArbLenData(buffer, getClientSocketHandle(), num_bytes, max_elements_);
}

template <template <typename> class C, typename T> void sendData(const C<T>& data_to_send)
{
    char* raw_ptr = (char*)data_to_send.getDataPointer();
    writeArbLenData(
        raw_ptr, getClientSocketHandle(), data_to_send.numElements() * sizeof(T), max_elements_);
}

inline void waitForAckInternal()
{
    waitForAck(getClientSocketHandle());
}

inline void sendTxList(const TxList& tx_list)
{
    sendTxListInternal(tx_list, getClientSocketHandle());
    waitForAckInternal();
}

#define TYPE_ERROR_MSG \
    "\n\n\033[31mTYPE ERROR: Only double supported for now!, Other types will come...\033[0m\n\n"

}  // namespace plot_tool

#endif
