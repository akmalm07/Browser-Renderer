#pragma once

#include "shared_function.h"

namespace renderer
{

    template<typename T>
    inline std::shared_ptr<T> SharedDataFunction<T>::get_state()

    {
        return _state;
    }

    template<typename T>
    inline SharedDataFunction<T>::SharedDataFunction()
        : _state(std::make_shared<T>()) 
    {
    }

    template<typename T>
    inline void SharedDataFunction<T>::add_function(std::function<void(std::shared_ptr<T>)> f)
    {
        auto state = _state;

        auto boundFunc = [state, f]() {
            f(state);
            };

        _functions.emplace_back(std::move(boundFunc));
    }


    template<typename T>
    inline void SharedDataFunction<T>::call_all() const

    {
        for (const auto& fn : _functions)
        {
            fn();
        }
    }
}