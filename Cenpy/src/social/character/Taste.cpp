#include <social/character/Taste.hpp>

namespace csc = cenpy::social::character;
csc::Taste::Taste(const std::unordered_map<MusicalTaste, int> &musicalAppreciation,
                  const std::unordered_map<FavoriteSubject, int> &favoriteSubjectAppreciation,
                  const std::unordered_map<SocioEconomicGroup, int> &socioEconomicGroupAppreciation)
    : musicalAppreciation(musicalAppreciation),
      favoriteSubjectAppreciation(favoriteSubjectAppreciation),
      socioEconomicGroupAppreciation(socioEconomicGroupAppreciation) {}

const std::unordered_map<csc::MusicalTaste, int> &csc::Taste::getMusicalAppreciation() const
{
  return musicalAppreciation;
}

const std::unordered_map<csc::FavoriteSubject, int> &csc::Taste::getFavoriteSubjectAppreciation() const
{
  return favoriteSubjectAppreciation;
}

const std::unordered_map<csc::SocioEconomicGroup, int> &csc::Taste::getSocioEconomicGroupAppreciation() const
{
  return socioEconomicGroupAppreciation;
}
