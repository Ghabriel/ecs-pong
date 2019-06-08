#pragma once

#include "EventListenerContainer.hpp"

namespace events {
    class EventManager {
     public:
        template<typename T>
        ListenerId registerEventListener(std::unique_ptr<T> instance) {
            ListenerId id = storage.nextListenerId++;
            storageOf<T>(storage).insert({ id, std::move(instance) });
            return id;
        }

        template<typename T>
        void enableEventListener(const std::string& event, ListenerId listener) {
            inactiveListeners<T>(storage)[event].erase(listener);
            activeListeners<T>(storage)[event].insert(listener);
        }

        template<typename T>
        void disableEventListener(const std::string& event, ListenerId listener) {
            activeListeners<T>(storage)[event].erase(listener);
            inactiveListeners<T>(storage)[event].insert(listener);
        }

        template<typename... Args>
        void emit(const std::string& event, const Args&... args) {
            using T = EventListener<Args...>;
            // Must make a copy because of potential iterator invalidation
            std::unordered_set<ListenerId> listeners = activeListeners<T>(storage)[event];
            ListenerStorage<T>& instances = storageOf<T>(storage);

            for (ListenerId id : listeners) {
                T& listener = *instances.at(id);
                listener(args...);
            }
        }

     private:
        EventListenerContainer storage;
    };
}
