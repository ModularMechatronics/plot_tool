#ifndef COMMUNICATION_UTILITIES_H_
#define COMMUNICATION_UTILITIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "communication/rx_list.h"
#include "communication/shared/transmission.h"

namespace plot_tool
{
#define NUM_HEADER_ELEMENTS 200

inline void waitForAck(const int socket_handle)
{
    char b[3];
    const int n = read(socket_handle, b, 3);
    assert((n == 3) && (b[0] == 'a') && (b[1] == 'c') && (b[2] == '#') && "Assertion failed!");
}

inline void sendAck(const int socket_handle)
{
    const char b[3] = {'a', 'c', '#'};
    const int n = write(socket_handle, b, 3);
    assert((n == 3) && "Failed to write all bytes!");
}

inline void writeArbLenData(const char* const buffer,
                            const int socket_handle,
                            const size_t num_elements,
                            const size_t max_elements)
{
    if (num_elements > max_elements)
    {
        const int remainder = static_cast<int>(num_elements) % static_cast<int>(max_elements);
        const int num_transmissions =
            static_cast<int>(num_elements) / static_cast<int>(max_elements);

        for (size_t k = 0; k < static_cast<size_t>(num_transmissions); k++)
        {
            const int n = write(socket_handle, buffer + max_elements * k, max_elements);
            assert(static_cast<size_t>(n) == max_elements);
            waitForAck(socket_handle);
        }

        if (remainder != 0)
        {
            const int n =
                write(socket_handle, buffer + max_elements * num_transmissions, remainder);
            assert(n == remainder);
            waitForAck(socket_handle);
        }
    }
    else
    {
        const int n = write(socket_handle, buffer, num_elements);
        assert(static_cast<size_t>(n) == num_elements);
        waitForAck(socket_handle);
    }
}

inline void receiveArbLenData(char* buffer,
                              const int socket_handle,
                              const size_t num_elements,
                              const size_t max_elements)
{
    if (num_elements > max_elements)
    {
        const int remainder = static_cast<int>(num_elements) % static_cast<int>(max_elements);
        const int num_transmissions =
            static_cast<int>(num_elements) / static_cast<int>(max_elements);

        for (size_t k = 0; k < static_cast<size_t>(num_transmissions); k++)
        {
            const int n = read(socket_handle, buffer + max_elements * k, max_elements);
            assert(static_cast<size_t>(n) == max_elements);
            sendAck(socket_handle);
        }

        if (remainder != 0)
        {
            const int n = read(socket_handle, buffer + max_elements * num_transmissions, remainder);
            assert(n == remainder);
            sendAck(socket_handle);
        }
    }
    else
    {
        const int n = read(socket_handle, buffer, num_elements);
        assert(static_cast<size_t>(n) == num_elements);
        sendAck(socket_handle);
    }
}

#define MAX_TX_LIST_BUFFER_SIZE 300

inline RxList receiveRxList(int socket_handle)
{
    char buffer[MAX_TX_LIST_BUFFER_SIZE];
    const int n = read(socket_handle, buffer, MAX_TX_LIST_BUFFER_SIZE);

    if (n == 0)
    {
        return RxList();
    }
    else
    {
        RxList rx_list(buffer);

        return rx_list;
    }
}

void sendTxListInternal(const TxList& tx_list, int socket_handle)
{
    char buffer[MAX_TX_LIST_BUFFER_SIZE];
    const size_t total_num_bytes = tx_list.totalNumBytesFromBuffer();
    assert((total_num_bytes < MAX_TX_LIST_BUFFER_SIZE) && "Data too big!");

    tx_list.fillBufferWithData(buffer);

    write(socket_handle, buffer, MAX_TX_LIST_BUFFER_SIZE);
}

}  // namespace plot_tool

#endif
