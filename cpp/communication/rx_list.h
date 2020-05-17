#ifndef RX_LIST_H_
#define RX_LIST_H_

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <utility>

#include "communication/rx_classes.h"
#include "communication/rx_list_helper_functions.h"
#include "communication/shared/plot_attributes.h"
#include "communication/shared/transmission.h"
#include "communication/shared/util_functions.h"

namespace plot_tool
{
class RxList
{
private:
    std::vector<RxReceiveBase*> vec;
    bool is_empty_;

public:
    std::vector<RxReceiveBase*> getVec() const
    {
        return vec;
    }

    RxList() : is_empty_(true) {}
    ~RxList()
    {
        for (auto v : vec)
        {
            delete v;
        }
    }

    RxReceiveBase* operator()(const size_t idx)
    {
        assert(idx < vec.size());
        return vec[idx];
    }

    bool isEmpty() const
    {
        return is_empty_;
    }

    RxList(const char* const receive_buffer) : is_empty_(false)
    {
        const size_t num_settings = static_cast<size_t>(receive_buffer[0]);
        size_t idx = 1;

        for (size_t k = 0; k < num_settings; k++)
        {
            Command cmd;
            plot_tool::fillObjectsFromBuffer(&(receive_buffer[idx]), cmd);
            idx = idx + sizeof(Command);
            std::pair<RxReceiveBase*, size_t> p =
                getPointerFromCommandType(cmd, &(receive_buffer[idx]));

            vec.push_back(p.first);
            idx = idx + p.second;
        }
    }

    RxList(const RxList& other_list) : is_empty_(false)
    {
        std::vector<RxReceiveBase*> other_vec = other_list.getVec();

        vec.resize(other_vec.size());

        for (size_t k = 0; k < other_vec.size(); k++)
        {
            RxReceiveBase* const ptr =
                getPointerFromCommandType(other_vec[k]->getCommandType(), other_vec[k]);
            vec[k] = ptr;
        }
    }

    RxList& operator=(const RxList& other_list)
    {
        if (this != &other_list)
        {
            for (auto v : vec)
            {
                delete v;
            }

            is_empty_ = false;

            std::vector<RxReceiveBase*> other_vec = other_list.getVec();

            vec.resize(other_vec.size());

            for (size_t k = 0; k < other_vec.size(); k++)
            {
                RxReceiveBase* const ptr =
                    getPointerFromCommandType(other_vec[k]->getCommandType(), other_vec[k]);
                vec[k] = ptr;
            }
        }

        return *this;
    }

    // TODO: Define move operator?

    void copy(const RxList& other_list)
    {
        for (auto v : vec)
        {
            delete v;
        }

        is_empty_ = false;

        std::vector<RxReceiveBase*> other_vec = other_list.getVec();

        vec.resize(other_vec.size());

        for (size_t k = 0; k < other_vec.size(); k++)
        {
            RxReceiveBase* const ptr =
                getPointerFromCommandType(other_vec[k]->getCommandType(), other_vec[k]);
            vec[k] = ptr;
        }
    }

    template <typename T> typename T::data_type getObjectData() const
    {
        const Command cmd = getCommandTypeFromClass<T>();
        assert(hasKey(cmd) && "Tried to get command that doesn't exist!");
        RxReceiveBase* ptr = nullptr;

        for (size_t k = 0; k < vec.size(); k++)
        {
            if (vec[k]->getCommandType() == cmd)
            {
                ptr = vec[k];
                break;
            }
        }

        assert(ptr && "Pointer is null!");

        const T* const type_ptr = dynamic_cast<T*>(ptr);

        return type_ptr->getData();
    }

    bool hasKey(const Command cmd) const
    {
        bool has_key = false;

        for (size_t k = 0; k < vec.size(); k++)
        {
            if (vec[k]->getCommandType() == cmd)
            {
                has_key = true;
                break;
            }
        }
        return has_key;
    }
};

}  // namespace plot_tool

#endif
