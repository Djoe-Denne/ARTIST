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
#include <cstring>
#include <string_view>
#include <ranges>
#include <map>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <common/exception/TraceableException.hpp>

namespace cenpy
{

    namespace collection_utils
    {

        struct StringHash
        {
            using is_transparent = void; // This makes it a transparent hash function

            size_t operator()(const std::string &s) const noexcept
            {
                return std::hash<std::string>{}(s);
            }

            size_t operator()(std::string_view s) const noexcept
            {
                return std::hash<std::string_view>{}(s);
            }

            size_t operator()(const char *s) const noexcept
            {
                // Be sure to handle null pointers if they are a possibility
                return std::hash<std::string_view>{}(s ? std::string_view(s) : std::string_view());
            }
        };

        struct StringEqual
        {
            using is_transparent = void; // This makes it a transparent equality comparator

            bool operator()(const std::string &lhs, const std::string &rhs) const noexcept
            {
                return lhs == rhs;
            }

            bool operator()(std::string_view lhs, const std::string &rhs) const noexcept
            {
                return lhs == rhs;
            }

            bool operator()(const std::string &lhs, std::string_view rhs) const noexcept
            {
                return lhs == rhs;
            }

            bool operator()(const char *lhs, const std::string &rhs) const noexcept
            {
                return lhs ? rhs == lhs : false;
            }

            bool operator()(const std::string &lhs, const char *rhs) const noexcept
            {
                return rhs ? lhs == rhs : false;
            }

            bool operator()(const char *lhs, const char *rhs) const noexcept
            {
                // Handle null pointers if they are a possibility
                return lhs && rhs ? std::strcmp(lhs, rhs) == 0 : lhs == rhs;
            }
        };

    }

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
