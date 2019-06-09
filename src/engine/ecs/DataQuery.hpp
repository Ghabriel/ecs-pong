#pragma once

#include <type_traits>
#include "ECS.hpp"
#include "lambda-argument-types.hpp"

namespace ecs {
    namespace __detail {
        template<typename T>
        struct Dispatcher;

        template<typename... Ts>
        struct Dispatcher<std::tuple<Ts...>> {
            template<typename ECS, typename Functor>
            void operator()(ECS& storage, Functor fn, Entity entity) {
                fn(entityData<std::decay_t<Ts>>(storage).at(entity)...);
            }
        };
    }

    template<typename ECS, typename T, typename... Ts>
    class DataQuery {
    public:
        explicit DataQuery(ECS& storage) : storage(storage) { }

        /**
         * Returns a `DataQuery` with an additional `U` filter.
         */
        template<typename U>
        DataQuery<ECS, T, Ts..., U> join() {
            return DataQuery<ECS, T, Ts..., U>(storage);
        }

        /**
         * Iterates over all entities that match this `DataQuery` filters,
         * executing a callback for each of them.
         *
         * The callback itself dictates which data is passed to it. Its
         * parameters can be either T, T& or const T& for any combination of
         * filtered Ts.
         *
         * **Warning**: `fn` **must not** change the iterated entities, e.g it
         * must not attach/detach components that are used as input.
         */
        template<typename Functor>
        void forEach(Functor fn) {
            __detail::Dispatcher<lambda_argument_types_t<Functor>> dispatcher;

            auto& allEntitiesData = entityData<T>(storage);

            if constexpr (sizeof...(Ts) > 0) {
                for (auto& [entity, data] : allEntitiesData) {
                    if (hasAllComponents<Ts...>(entity)) {
                        dispatcher(storage, fn, entity);
                    }
                }
            } else {
                for (auto& [entity, data] : allEntitiesData) {
                    dispatcher(storage, fn, entity);
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
    };
}
