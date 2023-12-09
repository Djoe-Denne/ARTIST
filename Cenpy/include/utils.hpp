#pragma once

#define MAP_TYPES_RETURN(MapType, KeyType, ValueType) \
    using RK = KeyType;                               \
    using RV = ValueType;                             \
    using ReturnType = MapType<RK, RV>;

#define MAP_TYPES_INPUT(MapType, KeyType, ValueType) \
    using IK = KeyType;                              \
    using IV = ValueType;                            \
    using InputType = MapType<IK, IV>;

#define LAMBDA_TYPES(Lambda) \
    common_utils::function_info<Lambda>

#define LAMBDA_TYPES_RETURN(Lambda) \
    LAMBDA_TYPES(Lambda)::return_type

#define LAMBDA_TYPES_INPUT(Lambda) \
    LAMBDA_TYPES(Lambda)::argument_type

#define MAP_TYPES(MapType, KeyLambda, ValueLambda)                                              \
    MAP_TYPES_RETURN(MapType, LAMBDA_TYPES_RETURN(KeyLambda), LAMBDA_TYPES_RETURN(ValueLambda)) \
    MAP_TYPES_INPUT(MapType, LAMBDA_TYPES_INPUT(KeyLambda), LAMBDA_TYPES_INPUT(ValueLambda))

#define RETURN_TYPES(MapType, KeyLambda, ValueLambda) \
    MapType<typename LAMBDA_TYPES_RETURN(KeyLambda), typename LAMBDA_TYPES_RETURN(ValueLambda)>

#include <string>
#include <ranges>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include <common/exception/TraceableException.hpp>

namespace cenpy
{

    namespace common_utils
    {

        // These two use a member function pointer type to deduce types for a callable (lambdas, mainly)
        template <typename T>
        struct memfun_type
        {
            using type = void;
        };
        template <typename Ret, typename Class, typename Arg>
        struct memfun_type<Ret (Class::*)(Arg) const>
        {
            using fn_type = std::function<Ret(Arg)>;
            using return_type = Ret;
            using argument_type = Arg;
        };
        // Nice clean template to get the type info of a callable type (lambdas mainly)
        template <typename F>
        using function_info = memfun_type<decltype(&F::operator())>;
    }

    /*/
    namespace collection_utils {
        template <template <typename, typename, typename...> class MapType, typename KeyMapper, typename ValueMapper, class IM,
                  typename = std::enable_if_t<std::is_base_of_v<MapType<typename IM::key_type, typename IM::mapped_type>, IM>>>
        auto map(const IM& mapToMap, const KeyMapper& keyMapper, const ValueMapper& valueMapper)
            -> RETURN_TYPES(MapType, Kestdexcept
            return ReturnType(result.begin(), result.end());
        }
    }
    */
    namespace json_utils
    {

        template <template <typename, typename, typename...> class MapType, typename KeyType, typename ValueType>
        auto nodeToMap(auto &node)
            -> MapType<KeyType, ValueType>
        {
            using ReturnType = MapType<KeyType, ValueType>;
            if (!node.is_object())
            {
                throw cenpy::common::exception::TraceableException<std::runtime_error>("Node is not an object");
            }
            ReturnType result = ReturnType();
            for (auto &[key, value] : node.items())
            {
                result[KeyType(key)] = ValueType(value);
            }
            return result;
        }
    }
}
