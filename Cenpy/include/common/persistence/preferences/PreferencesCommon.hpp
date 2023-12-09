#pragma once

#include <concepts>
#include <string>
#include <any>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define OS_WINDOWS
#elif __linux__
#define OS_LINUX
#elif __APPLE__
#define OS_MACOSX
#elif __ANDROID__
#define OS_ANDROID
#endif

namespace cenpy::common::persistence::preferences
{
    // A concept to check that T of Property is a typeb of PropertyVariant
    class PropertyValue;
    template <typename T>
    concept PropertyVariantType = std::same_as<T, int> || std::same_as<T, double> || std::same_as<T, std::string> || std::same_as<T, bool> || std::is_base_of_v<PropertyValue, T> || std::same_as<T, std::any>;

} // namespace preferences
