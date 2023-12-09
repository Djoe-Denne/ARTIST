#pragma once

#include <string>
#include <EnumClass.hpp>

namespace cenpy::social::character
{
    enum class PersonalityTypeEnum
    {
        INTROVERTED,
        EXTROVERTED,
        AMBITIOUS,
        CREATIVE,
        ANALYTICAL,
        EMPATHETIC,
        OPTIMISTIC,
        PESSIMISTIC,
        ADVENTUROUS,
        RESERVED,
        ENERGETIC
    };

    using PersonalityType = EnumClass<PersonalityTypeEnum>;
}
