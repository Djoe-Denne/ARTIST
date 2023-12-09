#include <yaml-cpp/yaml.h>
#include <common/persistence/preferences/Preferences.hpp>
#include <common/persistence/preferences/serializer/YamlSerializer.hpp>

namespace cenpy::common::persistence::preferences::serializer
{
    std::string YamlSerializer::getExtension() const
    {
        return "yaml";
    }

    YAML::Node PropertyToYaml(const Property &property)
    {
        YAML::Node yamlProperty;
        yamlProperty["key"] = property.getKey();

        // Assuming Property class has a stream insertion operator implemented
        std::ostringstream valueStream;
        valueStream << property;
        yamlProperty["value"] = valueStream.str();

        return yamlProperty;
    }

    void YamlToProperty(const YAML::Node &yamlProperty, Property &property)
    {
        property.read(yamlProperty["value"].as<std::string>());
    }

    YAML::Node SectionToYaml(const Section &section)
    {
        YAML::Node yamlSection;
        yamlSection["name"] = section.getName();

        YAML::Node yamlProperties;
        for (const auto &key : section.getKeys())
        {
            yamlProperties.push_back(PropertyToYaml(*section.getProperty(key)));
        }

        yamlSection["properties"] = yamlProperties;

        return yamlSection;
    }

    void YamlToSection(const YAML::Node &yamlSection, Section &section)
    {
        for (const auto &yamlProperty : yamlSection["properties"])
        {
            std::shared_ptr<Property> property = section.getProperty(yamlProperty["key"].as<std::string>());
            YamlToProperty(yamlProperty, *property);
        }
    }

    void YamlSerializer::serialize(std::ostream &os, const Property &property) const
    {
        YAML::Node yamlProperty = PropertyToYaml(property);
        os << yamlProperty << "\n";
    }

    void YamlSerializer::deserialize(std::istream &is, Property &property) const
    {
        std::string yamlString((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
        YAML::Node yamlProperty = YAML::Load(yamlString);
        YamlToProperty(yamlProperty, property);
    }

    void YamlSerializer::serialize(std::ostream &os, const Section &section) const
    {
        YAML::Node yamlSection = SectionToYaml(section);
        os << yamlSection << "\n";
    }

    void YamlSerializer::deserialize(std::istream &is, Section &section) const
    {
        std::string yamlString((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
        YAML::Node yamlSection = YAML::Load(yamlString);
        YamlToSection(yamlSection, section);
    }

    void YamlSerializer::serialize(std::ostream &os, const Preferences &preferences) const
    {
        YAML::Node yamlPreferences;

        for (const auto &sectionName : preferences.getSections())
        {
            yamlPreferences.push_back(SectionToYaml(preferences.getSection(sectionName)));
        }

        os << yamlPreferences << "\n";
    }

    void YamlSerializer::deserialize(std::istream &is, Preferences &preferences) const
    {
        std::string yamlString((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
        YAML::Node yamlPreferences = YAML::Load(yamlString);

        for (const auto &yamlSection : yamlPreferences)
        {
            Section section(yamlSection["name"].as<std::string>());
            YamlToSection(yamlSection, section);
            preferences.addSection(section);
        }
    }

} // namespace cenpy::common::persistence::preferences::serializer
