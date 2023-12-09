#include <gtest/gtest.h>
#include <common/persistence/preferences/PropertyValidators.hpp>

using namespace cenpy::common::persistence::preferences;

class PropertyValidatorTest : public ::testing::Test
{
};

class RegexPropertyValidatorTest : public ::testing::Test
{
};

class BetweenPropertyValidatorTest : public ::testing::Test
{
};

// Test case for PropertyValidator
TEST_F(PropertyValidatorTest, IsValid_ReturnsTrue)
{
    PropertyValidator validator;
    std::any value = 42;
    EXPECT_TRUE(validator.isValid(value));
}

// Test case for RegexPropertyValidator
TEST_F(RegexPropertyValidatorTest, IsValid_ReturnsTrue)
{
    std::string regex = "[0-9]+";
    RegexPropertyValidator validator(regex);
    std::any value = std::string("123");
    EXPECT_TRUE(validator.isValid(value));
}

TEST_F(RegexPropertyValidatorTest, IsValid_ReturnsFalse)
{
    std::string regex = "[0-9]+";
    RegexPropertyValidator validator(regex);
    std::any value = std::string("abc");
    EXPECT_FALSE(validator.isValid(value));
}

// Test case for BetweenPropertyValidator
TEST_F(BetweenPropertyValidatorTest, IsValid_ReturnsTrue)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = true;
    bool includeUpperBound = true;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = 42;
    EXPECT_TRUE(validator.isValid(value));
}

TEST_F(BetweenPropertyValidatorTest, IsValid_OutsideLowerBound_ReturnsFalse)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = true;
    bool includeUpperBound = true;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = -1;
    EXPECT_FALSE(validator.isValid(value));
}

TEST_F(BetweenPropertyValidatorTest, IsValid_OutsideUpperBound_ReturnsFalse)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = true;
    bool includeUpperBound = true;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = 101;
    EXPECT_FALSE(validator.isValid(value));
}

TEST_F(BetweenPropertyValidatorTest, IsValid_EqualLowerBoundIncluded_ReturnsTrue)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = true;
    bool includeUpperBound = true;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = 0;
    EXPECT_TRUE(validator.isValid(value));
}

TEST_F(BetweenPropertyValidatorTest, IsValid_EqualLowerBoundExcluded_ReturnsFalse)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = false;
    bool includeUpperBound = true;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = 0;
    EXPECT_FALSE(validator.isValid(value));
}

TEST_F(BetweenPropertyValidatorTest, IsValid_EqualUpperBoundIncluded_ReturnsTrue)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = true;
    bool includeUpperBound = true;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = 100;
    EXPECT_TRUE(validator.isValid(value));
}

TEST_F(BetweenPropertyValidatorTest, IsValid_EqualUpperBoundExcluded_ReturnsFalse)
{
    int min = 0;
    int max = 100;
    bool includeLowerBound = true;
    bool includeUpperBound = false;
    BetweenPropertyValidator<int> validator(min, max, includeLowerBound, includeUpperBound);
    std::any value = 100;
    EXPECT_FALSE(validator.isValid(value));
}
