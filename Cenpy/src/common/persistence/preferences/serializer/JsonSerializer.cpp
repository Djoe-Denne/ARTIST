#include <nlohmann/json.hpp>
#include <common/persistence/preferences/Preferences.hpp>
#include <common/persistence/preferences/serializer/JsonSerializer.hpp>

namespace cenpy::common::persistence::preferences::serializer
{
    using json = nlohmann::json;

    std::string JsonSerializer::getExtension() const
    {
        return "json";
    }

    json PropertyToJson(const Property &property)
    {
        json jsonProperty;
        jsonProperty["key"] = property.getKey();

        // Assuming Property class has a stream insertion operator implemented
        std::ostringstream valueStream;
        valueStream << property;
        jsonProperty["value"] = valueStream.str();

        return jsonProperty;
    }

    void JsonToProperty(const json &jsonProperty, Property &property)
    {
        property.read(jsonProperty["value"].get<std::string>());
    }

    json SectionToJson(const Section &section)
    {
        json jsonSection;
        jsonSection["name"] = section.getName();

        json jsonProperties;
        for (const auto &key : section.getKeys())
        {
            jsonProperties.push_back(PropertyToJson(*section.getProperty(key)));
        }

        jsonSection["properties"] = jsonProperties;

        return jsonSection;
    }

    void JsonToSection(const json &jsonSection, Section &section)
    {
        for (const auto &jsonProperty : jsonSection["properties"])
        {
            std::shared_ptr<Property> property = section.getProperty(jsonProperty["key"].get<std::string>());
            JsonToProperty(jsonProperty, *property);
        }
    }

    void JsonSerializer::serialize(std::ostream &os, const Property &property) const
    {
        json jsonProperty = PropertyToJson(property);
        os << jsonProperty.dump(2) << "\n"; // Pretty print with indentation level 2
    }

    void JsonSerializer::deserialize(std::istream &is, Property &property) const
    {
        json jsonProperty;
        is >> jsonProperty;
        JsonToProperty(jsonProperty, property);
    }

    void JsonSerializer::serialize(std::ostream &os, const Section &section) const
    {
        json jsonSection = SectionToJson(section);
        os << jsonSection.dump(2) << "\n"; // Pretty print with indentation level 2
    }

    void JsonSerializer::deserialize(std::istream &is, Section &section) const
    {
        json jsonSection;
        is >> jsonSection;
        JsonToSection(jsonSection, section);
    }

    void JsonSerializer::serialize(std::ostream &os, const Preferences &preferences) const
    {
        json jsonPreferences;

        for (const auto &sectionName : preferences.getSections())
        {
            jsonPreferences.push_back(SectionToJson(preferences.getSection(sectionName)));
        }

        os << jsonPreferences.dump(2) << "\n"; // Pretty print with indentation level 2
    }

    void JsonSerializer::deserialize(std::istream &is, Preferences &preferences) const
    {
        json jsonPreferences;
        is >> jsonPreferences;

        for (const auto &jsonSection : jsonPreferences)
        {
            Section section(jsonSection["name"].get<std::string>());
            JsonToSection(jsonSection, section);
            preferences.addSection(section);
        }
    }

} // namespace cenpy::common::persistence::preferences::serializer
