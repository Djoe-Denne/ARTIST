#include <social/character/Personality.hpp>
#include <common/exception/TraceableException.hpp>

namespace csc = cenpy::social::character;

csc::Personality::Personality(const Religion &religion, const Taste &taste, int languageAbility, const PersonalityType &personalityType, int sociability)
    : religion(religion), taste(taste), languageAbility(languageAbility), personalityType(personalityType), sociability(sociability) {}

int csc::Personality::getLanguageAbility() const
{
    return languageAbility;
}

void csc::Personality::setLanguageAbility(int value)
{
    if (value >= 1 && value <= 10)
    {
        languageAbility = value;
    }
    else
    {
        throw std::invalid_argument("Language ability must be between 1 and 10.");
    }
}

int csc::Personality::getSociability() const
{
    return sociability;
}

void csc::Personality::setSociability(int value)
{
    if (value >= 1 && value <= 10)
    {
        sociability = value;
    }
    else
    {
        throw std::invalid_argument("Sociability must be between 1 and 10.");
    }
}

const csc::PersonalityType &csc::Personality::getPersonalityType() const
{
    return personalityType;
}

const csc::Taste &csc::Personality::getTaste() const
{
    return taste;
}

const csc::Religion &csc::Personality::getReligion() const
{
    return religion;
}