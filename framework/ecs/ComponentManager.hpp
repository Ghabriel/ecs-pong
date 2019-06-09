#pragma once

#include "DataQuery.hpp"
#include "ECS.hpp"

namespace ecs {
    template<typename ECS>
    class GenericComponentManager {
     public:
        template<typename... Ts>
        Entity createEntity(Ts&&...);

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
        void query(Functor);

        template<typename T, typename... Ts, typename Functor>
        void mutatingQuery(Functor);

        template<typename T, typename... Args>
        void notify(Args&&...);

        template<typename T>
        DataQuery<ECS, T> findAll();

     private:
        ECS storage;

        template<typename T, typename... Ts, typename Functor>
        void internalQuery(Functor, ComponentData<T>&);
    };


    template<typename ECS>
    template<typename... Ts>
    inline Entity GenericComponentManager<ECS>::createEntity(Ts&&... data) {
        Entity id = storage.nextEntityId++;
        (addComponent<Ts>(id, std::forward<Ts>(data)), ...);
        return id;
    }

    template<typename ECS>
    template<typename T>
    inline void GenericComponentManager<ECS>::addComponent(Entity entity, T&& data) {
        entityData<std::decay_t<T>>(storage).insert({
            entity,
            std::forward<T>(data)
        });
    }

    template<typename ECS>
    template<typename T>
    inline void GenericComponentManager<ECS>::removeComponent(Entity entity) {
        entityData<T>(storage).erase(entity);
    }

    template<typename ECS>
    template<typename T>
    inline bool GenericComponentManager<ECS>::hasComponent(Entity entity) const {
        return entityData<T>(storage).count(entity);
    }

    template<typename ECS>
    template<typename T, typename... Ts>
    bool GenericComponentManager<ECS>::hasAllComponents(Entity entity) const {
        bool hasT = hasComponent<T>(entity);

        if constexpr (sizeof...(Ts) > 0) {
            return hasT && hasAllComponents<Ts...>(entity);
        } else {
            return hasT;
        }
    }

    template<typename ECS>
    template<typename T>
    inline T& GenericComponentManager<ECS>::getData(Entity entity) {
        return entityData<T>(storage).at(entity);
    }

    template<typename ECS>
    template<typename T, typename... Ts, typename Functor>
    inline void GenericComponentManager<ECS>::query(Functor fn) {
        ComponentData<T>& baseData = entityData<T>(storage);
        internalQuery<T, Ts...>(fn, baseData);
    }

    template<typename ECS>
    template<typename T, typename... Ts, typename Functor>
    inline void GenericComponentManager<ECS>::mutatingQuery(Functor fn) {
        // Makes a copy due to potential iterator invalidation
        ComponentData<T> baseData = entityData<T>(storage);
        internalQuery<T, Ts...>(fn, baseData);
    }

    template<typename ECS>
    template<typename T, typename... Args>
    inline void GenericComponentManager<ECS>::notify(Args&&... args) {
        mutatingQuery<T>([&](Entity, T& listener) {
            listener.fn(std::forward<Args>(args)...);
        });
    }

    template<typename ECS>
    template<typename T>
    inline DataQuery<ECS, T> GenericComponentManager<ECS>::findAll() {
        return DataQuery<ECS, T>(storage);
    }

    template<typename ECS>
    template<typename T, typename... Ts, typename Functor>
    inline void GenericComponentManager<ECS>::internalQuery(Functor fn, ComponentData<T>& baseData) {
        if constexpr (sizeof...(Ts) > 0) {
            for (auto& [entity, data] : baseData) {
                if (hasAllComponents<Ts...>(entity)) {
                    fn(entity, data, getData<Ts>(entity)...);
                }
            }
        } else {
            for (auto& [entity, data] : baseData) {
                fn(entity, data);
            }
        }
    }
}
