#pragma once

#include "ECS.hpp"

namespace ecs {
    template<typename T, typename... Ts>
    class DataQuery {
    public:
        explicit DataQuery(ECS& storage) : storage(storage) { }

        template<typename U>
        DataQuery<T, Ts..., U> join() {
            return DataQuery<T, Ts..., U>(storage);
        }

        template<typename... Us, typename Functor>
        void forEach(Functor fn) {
            auto& allEntitiesData = entityData<T>(storage);

            if constexpr (sizeof...(Ts) > 0) {
                for (auto& [entity, data] : allEntitiesData) {
                    if (hasAllComponents<Ts...>(entity)) {
                        fn(getData<Us>(entity)...);
                    }
                }
            } else {
                for (auto& [entity, data] : allEntitiesData) {
                    fn(entity, data);
                }
            }
        }

    private:
        ECS& storage;

        template<typename U>
        bool hasComponent(Entity entity) const {
            return entityData<U>(storage).count(entity);
        }

        template<typename U, typename... Us>
        bool hasAllComponents(Entity entity) const {
            bool hasT = hasComponent<U>(entity);

            if constexpr (sizeof...(Us) > 0) {
                return hasT && hasAllComponents<Us...>(entity);
            } else {
                return hasT;
            }
        }

        template<typename U>
        U& getData(Entity entity) {
            return entityData<U>(storage).at(entity);
        }
    };
}
