#pragma once

#include <unordered_map>
#include <string>
#include <social/character/MusicalTaste.hpp>
#include <social/character/FavoriteSubject.hpp>
#include <social/character/SocioEconomicGroup.hpp>

namespace cenpy::social::character
{
    class Taste
    {
    private:
        std::unordered_map<MusicalTaste, int> musicalAppreciation;
        std::unordered_map<FavoriteSubject, int> favoriteSubjectAppreciation;
        std::unordered_map<SocioEconomicGroup, int> socioEconomicGroupAppreciation;

    public:
        Taste(const std::unordered_map<MusicalTaste, int> &musicalAppreciation,
              const std::unordered_map<FavoriteSubject, int> &favoriteSubjectAppreciation,
              const std::unordered_map<SocioEconomicGroup, int> &socioEconomicGroupAppreciation);

        const std::unordered_map<MusicalTaste, int> &getMusicalAppreciation() const;
        const std::unordered_map<FavoriteSubject, int> &getFavoriteSubjectAppreciation() const;
        const std::unordered_map<SocioEconomicGroup, int> &getSocioEconomicGroupAppreciation() const;
    };
}
