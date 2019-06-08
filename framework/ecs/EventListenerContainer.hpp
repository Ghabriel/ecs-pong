#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "EventListener.hpp"

namespace events {
    using ListenerId = unsigned;

    template<typename T>
    using ListenerStorage = std::unordered_map<
        ListenerId,
        std::unique_ptr<T>
    >;

    using ListenerGroup = std::unordered_map<
        std::string,
        std::unordered_set<ListenerId>
    >;

    namespace __detail {
        template<typename T>
        struct FieldContainer {
            ListenerStorage<T> storage;
            ListenerGroup activeListeners;
            ListenerGroup inactiveListeners;

            static constexpr ListenerStorage<T> FieldContainer::*
                storageAddress = &FieldContainer::storage;

            static constexpr ListenerGroup FieldContainer::*
                activeAddress = &FieldContainer::activeListeners;

            static constexpr ListenerGroup FieldContainer::*
                inactiveAddress = &FieldContainer::inactiveListeners;
        };

        template<typename... Ts>
        struct GenericListenerContainer : FieldContainer<Ts>... {
            ListenerId nextListenerId = 0;
        };
    }

    using EventListenerContainer = __detail::GenericListenerContainer<
        EventListener<Team>
    >;

    template<typename T>
    constexpr ListenerStorage<T>& storageOf(EventListenerContainer& container) {
        constexpr auto field = __detail::FieldContainer<T>::storageAddress;
        return container.*field;
    }

    template<typename T>
    constexpr const ListenerStorage<T>& storageOf(const EventListenerContainer& container) {
        constexpr auto field = __detail::FieldContainer<T>::storageAddress;
        return container.*field;
    }

    template<typename T>
    constexpr ListenerGroup& activeListeners(EventListenerContainer& container) {
        constexpr auto field = __detail::FieldContainer<T>::activeAddress;
        return container.*field;
    }

    template<typename T>
    constexpr const ListenerGroup& activeListeners(const EventListenerContainer& container) {
        constexpr auto field = __detail::FieldContainer<T>::activeAddress;
        return container.*field;
    }

    template<typename T>
    constexpr ListenerGroup& inactiveListeners(EventListenerContainer& container) {
        constexpr auto field = __detail::FieldContainer<T>::inactiveAddress;
        return container.*field;
    }

    template<typename T>
    constexpr const ListenerGroup& inactiveListeners(const EventListenerContainer& container) {
        constexpr auto field = __detail::FieldContainer<T>::inactiveAddress;
        return container.*field;
    }
}
