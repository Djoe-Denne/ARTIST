#pragma once

#include <string>
#include <ranges>
#include <algorithm>
#include <magic_enum/magic_enum.hpp>

namespace cenpy
{
    template <class Enum>
    class EnumClass
    {
    public:
        constexpr EnumClass(Enum value) : value(value) {}
        EnumClass(std::string value);
        bool operator<=>(const EnumClass &other) const { return value <=> other.value; }
        bool operator==(const EnumClass &other) const { return value == other.value; }

        constexpr operator Enum() const { return value; }
        constexpr bool operator==(const Enum &other) const { return value == other; }
        operator std::string() const;
        std::string toString() const;

        explicit constexpr operator bool() const = delete;

    private:
        Enum value;
    };

    template <class Enum>
    EnumClass<Enum>::EnumClass(std::string value)
    {
        std::ranges::replace_if(
            value.begin(), value.end(), [](char c)
            { return std::string("- ").find(c) != std::string::npos; },
            '_');
        this->value = magic_enum::enum_cast<Enum>(value, magic_enum::case_insensitive).value();
    }

    template <class Enum>
    EnumClass<Enum>::operator std::string() const
    {
        return magic_enum::enum_name(this->value).data();
    }

    template <class Enum>
    std::string EnumClass<Enum>::toString() const
    {
        return static_cast<std::string>(*this);
    }
}

namespace std
{
    template <typename Enum>
    struct hash<cenpy::EnumClass<Enum>>
    {
        std::size_t operator()(cenpy::EnumClass<Enum> const &e) const noexcept
        {
            return std::hash<std::string>{}(e.toString());
        }
    };
};
