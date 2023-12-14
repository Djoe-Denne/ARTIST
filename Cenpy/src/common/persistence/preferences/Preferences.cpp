// preferences.cpp

#include <common/persistence/preferences/Preferences.hpp>

namespace cenpy::common::persistence::preferences
{

    /*******************************************************************
     * Section class implementation
     * *****************************************************************/

    Section::Section(const std::string &name)
        : m_name(name)
    {
    }

    std::string Section::getName() const
    {
        return m_name;
    }

    std::shared_ptr<Property> Section::getProperty(const std::string &key) const
    {
        if (!isValidKey(key))
        {
            throw std::runtime_error("Invalid key: " + key);
        }
        return m_properties.at(key);
    }

    std::vector<std::string> Section::getKeys() const
    {
        std::vector<std::string> keys;
        for (const auto &[key, property] : m_properties)
        {
            keys.push_back(key);
        }
        return keys;
    }

    bool Section::isValidKey(const std::string &key) const
    {
        return m_properties.find(key) != m_properties.end();
    }

    /*******************************************************************
     * Preferences class implementation
     * *****************************************************************/

    Preferences::Preferences(const std::string &appName, const std::string &filename, const std::shared_ptr<serializer::Serializer> &serializer)
        : m_appName(appName), m_filename(filename), m_serializer(serializer)
    {
    }

    const Section &Preferences::getSection(const std::string &name) const
    {
        auto it = m_sections.find(name);
        if (it != m_sections.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("Invalid section: " + name);
        }
    }

    Section &Preferences::getSection(const std::string &name)
    {
        auto it = m_sections.find(name);
        if (it != m_sections.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("Invalid section: " + name);
        }
    }

    std::vector<std::string> Preferences::getSections() const
    {
        std::vector<std::string> sections;
        for (const auto &[name, section] : m_sections)
        {
            sections.push_back(name);
        }
        return sections;
    }

    void Preferences::save()
    {
        saveToFile();
    }

    bool Preferences::fileExists() const
    {
        return m_serializer->fileExists(*this);
    }

    bool Preferences::load()
    {
        return loadFromFile();
    }

    bool Preferences::loadFromFile()
    {
        return m_serializer->loadFromFile(*this);
    }

    bool Preferences::saveToFile() const
    {
        return m_serializer->saveToFile(*this);
    }

    void Preferences::addSection(const Section &sectionObject)
    {
        m_sections[sectionObject.getName()] = sectionObject;
    }

} // namespace preferences
