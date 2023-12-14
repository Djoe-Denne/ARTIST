#pragma once

#include <string>
#include <fstream>

namespace cenpy::common::persistence::preferences
{
    class Preferences;
    class Section;
    class Property;

    namespace serializer
    {

        class Serializer
        {
        public:
            virtual ~Serializer() = default;

            bool fileExists(const Preferences &preferences) const;
            void ensureSeriability(const Preferences &preferences) const;
            std::string getAppDir(const Preferences &preferences) const;
            std::string getPreferencesFilePath(const Preferences &preferences) const;

            bool saveToFile(const Preferences &preferences) const;
            bool loadFromFile(Preferences &preferences) const;

        protected:
            virtual void serialize(std::ostream &os, const Preferences &preferences) const = 0;
            virtual void deserialize(std::istream &is, Preferences &preferences) const = 0;
            virtual void serialize(std::ostream &os, const Section &section) const = 0;
            virtual void deserialize(std::istream &is, Section &section) const = 0;
            virtual void serialize(std::ostream &os, const Property &property) const = 0;
            virtual void deserialize(std::istream &is, Property &property) const = 0;
            virtual std::string getExtension() const = 0;
            virtual std::string trim(const std::string &str) const;
        };
    }
} // namespace cenpy::common::persistence::preferences::serializer
