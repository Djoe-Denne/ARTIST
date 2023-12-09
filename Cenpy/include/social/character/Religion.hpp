#pragma once

#include <string>
#include <EnumClass.hpp>
namespace cenpy::social::character
{
    enum class ReligionEnum
    {
        CHRISTIANITY,
        ISLAM,
        BUDDHISM,
        JUDAISM,
        ATHEISM
    };

    using Religion = EnumClass<ReligionEnum>;
}