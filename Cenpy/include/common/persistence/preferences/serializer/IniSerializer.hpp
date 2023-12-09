#pragma once

#include <fstream>
#include <common/persistence/preferences/serializer/Serializer.hpp>

namespace cenpy::common::persistence::preferences
{
    class Preferences;
    class Section;
    class Property;

    namespace serializer
    {
        class IniSerializer : public Serializer
        {
        protected:
            virtual void serialize(std::ostream &os, const Preferences &preferences) const override;
            virtual void deserialize(std::istream &is, Preferences &preferences) const override;
            virtual void serialize(std::ostream &os, const Section &section) const override;
            virtual void deserialize(std::istream &is, Section &section) const override;
            virtual void serialize(std::ostream &os, const Property &property) const override;
            virtual void deserialize(std::istream &is, Property &property) const override;
            virtual std::string getExtension() const override;
        };
    }
} // namespace cenpy::common::persistence::preferences::serializer
