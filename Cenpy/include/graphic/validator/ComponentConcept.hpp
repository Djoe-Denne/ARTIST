#pragma once

#include <memory>
#include <type_traits>

namespace cenpy::graphic::validator
{
    // Concept to check if a type has a static method do with the specified signature
    template <typename T, typename C>
    concept HasOnMethod = requires(std::shared_ptr<C> context) {
        {
            T::on(context)
        } -> std::same_as<void>;
    };

    template <typename C>
    concept HasComponent = requires {
        typename C;
    };
}