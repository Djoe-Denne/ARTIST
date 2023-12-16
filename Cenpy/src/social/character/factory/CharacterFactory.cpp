#include <common/exception/TraceableException.hpp>
#include <social/character/factory/CharacterFactory.hpp>
#include <fstream>
#include <iostream>
#include <utils.hpp>
#include <map>

using json = nlohmann::json;

namespace cenpy
{

    namespace csc = social::character;
    namespace cscf = csc::factory;

    csc::Character cscf::CharacterFactory::createCharacter(const std::string &name)
    {
        try
        {
            std::ifstream jsonFile("test\\game\\resources\\assets\\social\\character\\" + name + ".json");
            if (!jsonFile.is_open())
            {
                throw common::exception::TraceableException<std::invalid_argument>("Error loading character from JSON: File not found");
            }
            json characterData;
            jsonFile >> characterData;

            return Character(
                characterData["name"].template get<std::string>(),
                characterData["age"],
                characterData["origin"].template get<std::string>(),
                characterData["sex"],
                createPersonality(characterData["personality"]));
        }
        catch (const std::exception &e)
        {
            throw common::exception::TraceableException<std::invalid_argument>("Error loading character from JSON: " + std::string(e.what()));
        }
    }

    csc::Personality cscf::CharacterFactory::createPersonality(const json &personalityData)
    {
        try
        {
            return csc::Personality(
                csc::Religion(personalityData["religion"].template get<std::string>()),
                csc::Taste(
                    json_utils::nodeToMap<std::unordered_map, csc::MusicalTaste, int>(personalityData["taste"]["musical_appreciation"]),
                    json_utils::nodeToMap<std::unordered_map, csc::FavoriteSubject, int>(personalityData["taste"]["favorite_subject_appreciation"]),
                    json_utils::nodeToMap<std::unordered_map, csc::SocioEconomicGroup, int>(personalityData["taste"]["socio_economic_group_appreciation"])),
                personalityData["language_ability"],
                csc::PersonalityType(personalityData["personality_type"].template get<std::string>()),
                personalityData["sociability"]);
        }
        catch (const std::exception &e)
        {
            throw common::exception::TraceableException<std::invalid_argument>("Error loading personality from JSON: " + std::string(e.what()));
        }
    }
} // namespace cenpy
