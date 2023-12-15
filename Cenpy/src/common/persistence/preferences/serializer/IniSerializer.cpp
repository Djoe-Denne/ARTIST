#include <algorithm>
#include <ranges>
#include <common/exception/TraceableException.hpp>
#include <common/persistence/preferences/Preferences.hpp>
#include <common/persistence/preferences/serializer/IniSerializer.hpp>

namespace cenpy::common::persistence::preferences::serializer
{
    std::string IniSerializer::getExtension() const
    {
        return "ini";
    }

    void IniSerializer::serialize(std::ostream &os, const Property &property) const
    {
        os << property.getKey() << "=" << property << "\n";
    }

    void IniSerializer::deserialize(std::istream &is, Property &property) const
    {
        std::string line = "";
        std::getline(is, line);
        std::size_t separatorPos = line.find('=');
        if (separatorPos != std::string::npos)
        {
            std::string key = line.substr(0, separatorPos);
            if (property.getKey() == key)
            {
                std::string value = line.substr(separatorPos + 1);
                property.read(value);
            }
            else
            {
                throw exception::TraceableException<std::runtime_error>("Invalid key, it's only possible to read pre-defined keys: " + key);
            }
        }
    }

    void IniSerializer::serialize(std::ostream &os, const Section &section) const
    {
        os << "[" << section.getName() << "]\n";
        for (const auto &key : section.getKeys())
        {
            serialize(os, *section.getProperty(key));
        }
    }

    void IniSerializer::deserialize(std::istream &is, Section &section) const
    {
        // Read lines until the next section or the end of the file
        std::string line;
        while (std::getline(is, line))
        {
            line = trim(line);
            // Trim leading and trailing whitespaces
            std::erase_if(line, ::isspace);

            // Ignore comments and empty lines
            if (line.empty() || line[0] == ';')
                continue;

            // Split the line into key-value pair
            std::size_t separatorPos = line.find('=');
            if (separatorPos != std::string::npos)
            {
                std::string key = line.substr(0, separatorPos);
                if (section.isValidKey(key))
                {
                    std::istringstream valueStream(line);
                    deserialize(valueStream, *section.getProperty(key));
                }
                else
                {
                    throw exception::TraceableException<std::runtime_error>("Invalid key, it's only possible to read pre-defined keys: " + key);
                }
            }

            if (is.peek() == '[')
            {
                break;
            }
        }
    }

    // Operator overloads for Preferences serialization and deserialization
    void IniSerializer::serialize(std::ostream &os, const Preferences &preferences) const
    {
        for (const auto &sectionName : preferences.getSections())
        {
            serialize(os, preferences.getSection(sectionName));
        }
    }

    void IniSerializer::deserialize(std::istream &is, Preferences &preferences) const
    {
        // Read lines until the end of the file
        std::string line;
        while (std::getline(is, line))
        {
            line = trim(line);
            std::vector<std::string> sectionNames = preferences.getSections();
            // Trim leading and trailing whitespaces
            std::string trimmedLine = line;
            std::erase_if(trimmedLine, ::isspace);

            // Ignore comments and empty lines
            if (trimmedLine.empty() || trimmedLine[0] == ';')
                continue;

            // Check if the line is the start of a new section
            if (trimmedLine[0] == '[' && trimmedLine.back() == ']')
            {
                std::string sectionName = trimmedLine.substr(1, trimmedLine.size() - 2);
                if (std::ranges::find(sectionNames, sectionName) != sectionNames.end())
                {
                    deserialize(is, preferences.getSection(sectionName));
                }
                else
                {
                    throw exception::TraceableException<std::runtime_error>("Section doesn't exist, can read only pre-defined sections");
                }
            }
            else
            {
                throw exception::TraceableException<std::runtime_error>("Invalid line, it's only possible to read sections and properties");
            }
        }
    }

} // namespace cenpy::common::persistence::preferences::serializer
