#pragma once

namespace events {
    template<typename... Args>
    class EventListener {
     public:
        virtual ~EventListener() = default;

        virtual void operator()(const Args&...) = 0;
    };
}
