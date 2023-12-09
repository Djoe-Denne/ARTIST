#pragma once

#include <social/character/PersonalityType.hpp>
#include <social/character/Religion.hpp>
#include <social/character/Taste.hpp>
#include <string>

namespace cenpy::social::character
{
    class Personality
    {
    private:
        Religion religion;
        Taste taste;
        int languageAbility;
        PersonalityType personalityType;
        int sociability;

    public:
        Personality(const Religion &religion, const Taste &taste, int languageAbility, const PersonalityType &personalityType, int sociability);

        int getLanguageAbility() const;
        void setLanguageAbility(int value);
        int getSociability() const;
        void setSociability(int value);
        const PersonalityType &getPersonalityType() const;
        const Taste &getTaste() const;
        const Religion &getReligion() const;
    };
}
