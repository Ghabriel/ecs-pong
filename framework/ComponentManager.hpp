#pragma once

#include "ECS.hpp"

namespace ecs {
    class ComponentManager {
     public:
        Entity createEntity();

        template<typename T>
        void addComponent(Entity, T&&);

        template<typename T>
        void removeComponent(Entity);

        template<typename T>
        bool hasComponent(Entity) const;

        template<typename T, typename... Ts>
        bool hasAllComponents(Entity) const;

        template<typename T>
        T& getData(Entity);

        template<typename T, typename... Ts, typename Functor>
        void query(Functor fn);

     private:
        ECS storage;
    };


    inline Entity ComponentManager::createEntity() {
        return storage.nextEntityId++;
    }

    template<typename T>
    inline void ComponentManager::addComponent(Entity entity, T&& data) {
        entityData<std::decay_t<T>>(storage).insert({
            entity,
            std::forward<T>(data)
        });
    }

    template<typename T>
    inline void ComponentManager::removeComponent(Entity entity) {
        entityData<T>(storage).erase(entity);
    }

    template<typename T>
    inline bool ComponentManager::hasComponent(Entity entity) const {
        return entityData<T>(storage).count(entity);
    }

    template<typename T, typename... Ts>
    bool ComponentManager::hasAllComponents(Entity entity) const {
        bool hasT = hasComponent<T>(entity);

        if constexpr (sizeof...(Ts) > 0) {
            return hasT && hasAllComponents<Ts...>(entity);
        } else {
            return hasT;
        }
    }

    template<typename T>
    inline T& ComponentManager::getData(Entity entity) {
        return entityData<T>(storage).at(entity);
    }

    template<typename T, typename... Ts, typename Functor>
    inline void ComponentManager::query(Functor fn) {
        auto& allEntitiesData = entityData<T>(storage);

        if constexpr (sizeof...(Ts) > 0) {
            for (auto& [entity, data] : allEntitiesData) {
                if (hasAllComponents<Ts...>(entity)) {
                    fn(entity, data, getData<Ts>(entity)...);
                }
            }
        } else {
            for (auto& [entity, data] : allEntitiesData) {
                fn(entity, data);
            }
        }
    }
}