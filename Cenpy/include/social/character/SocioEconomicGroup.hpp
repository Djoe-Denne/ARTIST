#pragma once

#include <string>
#include <EnumClass.hpp>

namespace cenpy::social::character
{
    enum class SocioEconomicGroupEnum
    {
        RICH,
        UPPER_MIDDLE_CLASS,
        MIDDLE_CLASS,
        POOR
    };

    using SocioEconomicGroup = EnumClass<SocioEconomicGroupEnum>;
}