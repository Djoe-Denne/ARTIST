#pragma once

#include <string>
#include <EnumClass.hpp>

namespace cenpy::social::character
{
    enum class FavoriteSubjectEnum
    {
        MATH,
        SCIENCE,
        LITERATURE,
        PHILOSOPHY,
        ECONOMICS,
        GEOGRAPHY,
        LANGUAGES,
        HISTORY,
        ART,
        MUSIC,
        PHYSICAL_EDUCATION,
        COMPUTER_SCIENCE,
        FOREIGN_LANGUAGE,
        OTHER
    };

    using FavoriteSubject = EnumClass<FavoriteSubjectEnum>;
}
