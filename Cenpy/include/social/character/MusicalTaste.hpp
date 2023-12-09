#pragma once

#include <string>
#include <EnumClass.hpp>

namespace cenpy::social::character
{
    enum class MusicalTasteEnum
    {
        CLASSICAL,
        ROCK,
        POP,
        JAZZ,
        HIP_HOP,
        RAP,
        OTHER
    };

    using MusicalTaste = EnumClass<MusicalTasteEnum>;
}
