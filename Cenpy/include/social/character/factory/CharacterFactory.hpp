#pragma once

#include <social/character/Character.hpp>
#include <nlohmann/json.hpp>

namespace cenpy::social::character::factory
{
    class CharacterFactory
    {
    public:
        static Character createCharacter(const std::string &name);

    private:
        static Personality createPersonality(const nlohmann::json &personalityData);
    };
}