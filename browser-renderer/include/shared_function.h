#pragma once

#include "config.h"


namespace renderer
{


    template <typename T>
    class SharedDataFunction
    {
    public:

        SharedDataFunction();

        void add_function(std::function<void(std::shared_ptr<T>)> f);

        void call_all() const;

        std::shared_ptr<T> get_state();

    private:
        std::shared_ptr<T> _state;
        std::vector<std::function<void()>> _functions;
    };

}

#include "shared_function.inl"