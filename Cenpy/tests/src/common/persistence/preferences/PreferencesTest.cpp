#include <gtest/gtest.h>
#include <filesystem>
#include <common/persistence/preferences/Preferences.hpp>
#include <common/persistence/preferences/serializer/JsonSerializer.hpp>
#include <common/persistence/preferences/serializer/YamlSerializer.hpp>
#include <common/persistence/preferences/serializer/XmlSerializer.hpp>

namespace cenpy::common::persistence::preferences
{
    namespace serializer
    {
        std::string getAppDataPath();
    }

    class ResolutionPropertyValue : public PropertyValue
    {
    public:
        ResolutionPropertyValue(const int &width, const int &height)
            : m_width(width), m_height(height)
        {
        }

        std::string toString() const
        {
            return std::to_string(m_width) + "x" + std::to_string(m_height);
        }

        void read(std::istream &is) override
        {
            std::string value;
            is >> value;
            std::size_t separatorPos = value.find('x');
            if (separatorPos != std::string::npos)
            {
                std::string width = value.substr(0, separatorPos);
                std::string height = value.substr(separatorPos + 1);
                m_width = std::stoi(width);
                m_height = std::stoi(height);
            }
        }

        std::ostream &write(std::ostream &os) const override
        {
            os << toString();
            return os;
        }

        const int &getWidth() const
        {
            return m_width;
        }

        const int &getHeight() const
        {
            return m_height;
        }

    private:
        int m_width;
        int m_height;
    };

    // Define a custom validator for integer properties
    class IntegerValidator : public PropertyValidator
    {
    public:
        bool isValid(const std::any &value) const override
        {
            return std::any_cast<int>(value) >= 0; // Example: Only accept non-negative integers
        }
    };
} // namespace cenpy::common::persistence::preferences

using namespace cenpy::common::persistence::preferences;

// Define a fixture class for the Preferences tests
class PreferencesTest : public ::testing::Test
{
public:
    constexpr static const std::string TEST_APP_NAME = "PreferencesTest";
    constexpr static const std::string TEST_FILE_NAME = "test";

    void TearDown() override
    {
        // Remove the test directory
        std::filesystem::remove_all(serializer::getAppDataPath() + "/" + TEST_APP_NAME);
    }
};

// Define a fixture class for the Section tests
class SectionTest : public ::testing::Test
{
};

// Test the Section class
TEST_F(SectionTest, GetName)
{
    Section section("test");
    EXPECT_EQ("test", section.getName());
}

TEST_F(SectionTest, CreateProperty)
{
    Section section("test");
    section.createProperty("key", 10, std::make_unique<IntegerValidator>());
    EXPECT_EQ(10, section.get<int>("key"));
}

TEST_F(SectionTest, CreateCustomProperty)
{
    Section section("test");
    section.createProperty<ResolutionPropertyValue>("key", ResolutionPropertyValue(800, 600));
    EXPECT_EQ(800, section.get<ResolutionPropertyValue>("key")->getWidth());
    EXPECT_EQ(600, section.get<ResolutionPropertyValue>("key")->getHeight());
}

TEST_F(SectionTest, GetProperty)
{
    Section section("test");
    section.createProperty("key", 10);
    std::shared_ptr<Property> property = section.getProperty("key");
    EXPECT_EQ(10, property->getValue<int>());
}

TEST_F(SectionTest, Set)
{
    Section section("test");
    section.createProperty("key", 10);
    section.set("key", 20);
    EXPECT_EQ(20, section.get<int>("key"));
}

TEST_F(SectionTest, IsValidKey)
{
    Section section("test");
    section.createProperty("key", 10);
    EXPECT_TRUE(section.isValidKey("key"));
}

TEST_F(SectionTest, IsNotValidKey)
{
    Section section("test");
    EXPECT_FALSE(section.isValidKey("key"));
}

TEST_F(PreferencesTest, SetAndGet)
{
    Preferences preferences("app", "file");
    Section section("section");
    section.createProperty("key", 1);
    preferences.addSection(section);
    preferences.set("section", "key", 10);
    EXPECT_EQ(10, preferences.get<int>("section", "key"));
}

TEST_F(PreferencesTest, Save)
{
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    EXPECT_FALSE(preferences.fileExists());
    Section section("section");
    section.createProperty("key", 10);
    section.createProperty("key2", 1.8);
    section.createProperty("key3", "test");
    section.createProperty("key4", true);
    preferences.addSection(section);
    preferences.save();
    EXPECT_TRUE(preferences.fileExists());
}

TEST_F(PreferencesTest, SaveJson)
{
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME, std::make_shared<serializer::JsonSerializer>());
    EXPECT_FALSE(preferences.fileExists());
    Section section("section");
    section.createProperty("key", 10);
    section.createProperty("key2", 1.8);
    section.createProperty("key3", "test");
    section.createProperty("key4", true);
    preferences.addSection(section);
    preferences.save();
    EXPECT_TRUE(preferences.fileExists());
}

TEST_F(PreferencesTest, SaveYaml)
{
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME, std::make_shared<serializer::YamlSerializer>());
    EXPECT_FALSE(preferences.fileExists());
    Section section("section");
    section.createProperty("key", 10);
    section.createProperty("key2", 1.8);
    section.createProperty("key3", "test");
    section.createProperty("key4", true);
    preferences.addSection(section);
    preferences.save();
    EXPECT_TRUE(preferences.fileExists());
}

TEST_F(PreferencesTest, SaveXml)
{
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME, std::make_shared<serializer::XmlSerializer>());
    EXPECT_FALSE(preferences.fileExists());
    Section section("section");
    section.createProperty("key", 10);
    section.createProperty("key2", 1.8);
    section.createProperty("key3", "test");
    section.createProperty("key4", true);
    preferences.addSection(section);
    preferences.save();
    EXPECT_TRUE(preferences.fileExists());
}

TEST_F(PreferencesTest, Load)
{
    std::filesystem::create_directories(PreferencesTest::TEST_APP_NAME);
    std::ofstream file(serializer::getAppDataPath() + "/" + PreferencesTest::TEST_APP_NAME + "/" + PreferencesTest::TEST_FILE_NAME + ".ini");
    file << "[section]\n"
            "key=10\n"
            "key2=1.8\n"
            "key3=test\n"
            "key4=true\n";
    file.close();
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section("section");
    section.createProperty("key", 0);
    section.createProperty("key2", 0.0);
    section.createProperty("key3", "");
    section.createProperty("key4", false);
    preferences.addSection(section);
    EXPECT_TRUE(preferences.load());
    EXPECT_EQ(10, preferences.get<int>("section", "key"));
    EXPECT_EQ(1.8, preferences.get<double>("section", "key2"));
    EXPECT_EQ("test", preferences.get<std::string>("section", "key3"));
    EXPECT_EQ(true, preferences.get<bool>("section", "key4"));
}

TEST_F(PreferencesTest, LoadWithInvalidKey)
{
    std::filesystem::create_directories(PreferencesTest::TEST_APP_NAME);
    std::ofstream file(serializer::getAppDataPath() + "/" + PreferencesTest::TEST_APP_NAME + "/" + PreferencesTest::TEST_FILE_NAME + ".ini");
    file << "[section]\n"
            "key=10\n"
            "key2=1.8\n"
            "key3=test\n"
            "key4=true\n";
    file.close();
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section("section");
    section.createProperty("key", 0);
    section.createProperty("key2", 0.0);
    section.createProperty("key3", "");
    section.createProperty("key4", false);
    section.createProperty("key5", 0);
    preferences.addSection(section);
    EXPECT_TRUE(preferences.load());
    EXPECT_EQ(10, preferences.get<int>("section", "key"));
    EXPECT_EQ(1.8, preferences.get<double>("section", "key2"));
    EXPECT_EQ("test", preferences.get<std::string>("section", "key3"));
    EXPECT_EQ(true, preferences.get<bool>("section", "key4"));
    EXPECT_EQ(0, preferences.get<int>("section", "key5"));
}

TEST_F(PreferencesTest, SaveOnFirstLoad)
{
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section("section");
    section.createProperty("key", 10);
    preferences.addSection(section);
    EXPECT_FALSE(preferences.load());
    EXPECT_EQ(10, preferences.get<int>("section", "key"));

    Preferences preferences2(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section2("section");
    section2.createProperty("key", 20);
    preferences2.addSection(section2);
    EXPECT_TRUE(preferences2.load());
    EXPECT_EQ(10, preferences2.get<int>("section", "key"));
}

TEST_F(PreferencesTest, SaveWithCustomPropery)
{
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section("section");
    section.createProperty<ResolutionPropertyValue>("key", ResolutionPropertyValue(800, 600));
    preferences.addSection(section);
    preferences.save();
    EXPECT_TRUE(preferences.fileExists());

    Preferences preferences2(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section2("section");
    section2.createProperty<ResolutionPropertyValue>("key", ResolutionPropertyValue(1920, 1080));
    preferences2.addSection(section2);
    EXPECT_TRUE(preferences2.load());
    EXPECT_EQ(800, preferences2.get<ResolutionPropertyValue>("section", "key")->getWidth());
    EXPECT_EQ(600, preferences2.get<ResolutionPropertyValue>("section", "key")->getHeight());
}

TEST_F(PreferencesTest, LoadWithCustomPropery)
{
    std::filesystem::create_directories(PreferencesTest::TEST_APP_NAME);
    std::ofstream file(PreferencesTest::TEST_APP_NAME + "/" + PreferencesTest::TEST_FILE_NAME + ".ini");
    file << "[section]\n"
            "key=1920x1080\n";
    file.close();
    Preferences preferences(PreferencesTest::TEST_APP_NAME, PreferencesTest::TEST_FILE_NAME);
    Section section("section");
    section.createProperty<ResolutionPropertyValue>("key", ResolutionPropertyValue(800, 600));
    preferences.addSection(section);
    EXPECT_TRUE(preferences.load());
    EXPECT_EQ(1920, preferences.get<ResolutionPropertyValue>("section", "key")->getWidth());
    EXPECT_EQ(1080, preferences.get<ResolutionPropertyValue>("section", "key")->getHeight());
}