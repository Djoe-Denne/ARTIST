#include <gtest/gtest.h>
#include <social/character/factory/CharacterFactory.hpp>

namespace csc = cenpy::social::character;
namespace cscf = csc::factory;
// Define a test fixture
class CharacterFactoryTest : public ::testing::Test
{
protected:
    cscf::CharacterFactory characterFactory;
};

// Test case for successful character creation
TEST_F(CharacterFactoryTest, CreateCharacterSuccess)
{
    // Assuming you have a valid JSON file for testing
    const std::string validCharacterName = "John Doe";

    csc::Character character = characterFactory.createCharacter(validCharacterName);
    // Add more assertions based on the expected values in the valid JSON file
    EXPECT_EQ(character.getName(), validCharacterName);
    EXPECT_EQ(character.getAge(), 30);
    EXPECT_EQ(character.getOrigin(), "New York");
    EXPECT_EQ(character.getSex(), true);
    EXPECT_EQ(character.getDisplayable(), validCharacterName);
    EXPECT_EQ(character.getRelationships().size(), 0);
    EXPECT_EQ(character.getPersonality().getReligion(), csc::ReligionEnum::CHRISTIANITY);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::ROCK), 7);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::POP), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::JAZZ), 4);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::CLASSICAL), 3);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::RAP), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::HIP_HOP), 5);
    EXPECT_EQ(character.getPersonality().getTaste().getMusicalAppreciation().at(csc::MusicalTasteEnum::OTHER), 5);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::LITERATURE), 7);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::ART), 4);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::ECONOMICS), 5);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::COMPUTER_SCIENCE), 7);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::SCIENCE), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::GEOGRAPHY), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::MATH), 8);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::HISTORY), 5);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::LANGUAGES), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::MUSIC), 5);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::OTHER), 5);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::PHILOSOPHY), 4);
    EXPECT_EQ(character.getPersonality().getTaste().getFavoriteSubjectAppreciation().at(csc::FavoriteSubjectEnum::PHYSICAL_EDUCATION), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getSocioEconomicGroupAppreciation().at(csc::SocioEconomicGroupEnum::RICH), 8);
    EXPECT_EQ(character.getPersonality().getTaste().getSocioEconomicGroupAppreciation().at(csc::SocioEconomicGroupEnum::UPPER_MIDDLE_CLASS), 7);
    EXPECT_EQ(character.getPersonality().getTaste().getSocioEconomicGroupAppreciation().at(csc::SocioEconomicGroupEnum::MIDDLE_CLASS), 6);
    EXPECT_EQ(character.getPersonality().getTaste().getSocioEconomicGroupAppreciation().at(csc::SocioEconomicGroupEnum::POOR), 4);
    EXPECT_EQ(character.getPersonality().getLanguageAbility(), 8);
    EXPECT_EQ(character.getPersonality().getPersonalityType(), csc::PersonalityTypeEnum::EXTROVERTED);
    EXPECT_EQ(character.getPersonality().getSociability(), 7);

    // Add more expectations based on your character data structure
}

// Test case for handling file not found
TEST_F(CharacterFactoryTest, CreateCharacterFileNotFound)
{
    const std::string invalidCharacterName = "nonexistent_character";

    ASSERT_THROW(
        characterFactory.createCharacter(invalidCharacterName),
        std::invalid_argument);
}
