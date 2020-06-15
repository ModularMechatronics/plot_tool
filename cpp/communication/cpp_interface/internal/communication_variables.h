#ifndef PLOT_TOOL_COMMUNICATION_VARIABLES_H_
#define PLOT_TOOL_COMMUNICATION_VARIABLES_H_

#include <mutex>

namespace plot_tool
{
inline std::mutex& _Var_comm_thread_mutex()
{
    static std::mutex mtx;
    return mtx;
}

// Client socket handle
inline int& _Var_client_socket_handle()
{
    static int client_socket_handle;
    return client_socket_handle;
}

inline void setClientSocketHandle(const int new_val)
{
    std::lock_guard<std::mutex> guard(_Var_comm_thread_mutex());
    _Var_client_socket_handle() = new_val;
}

inline int getClientSocketHandle()
{
    const int client_socket_handle = _Var_client_socket_handle();
    return client_socket_handle;
}

// Client is initialized
inline bool& _Var_client_is_initialized()
{
    static bool client_is_initialized = false;
    return client_is_initialized;
}

inline void setClientIsInitialized(const bool new_val)
{
    std::lock_guard<std::mutex> guard(_Var_comm_thread_mutex());
    _Var_client_is_initialized() = new_val;
}

inline bool getClientIsInitialized()
{
    const bool client_is_initialized = _Var_client_is_initialized();
    return client_is_initialized;
}

}  // namespace plot_tool

#endif
