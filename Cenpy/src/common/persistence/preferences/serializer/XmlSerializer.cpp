#include <pugixml.hpp>
#include <common/persistence/preferences/Preferences.hpp>
#include <common/persistence/preferences/serializer/XmlSerializer.hpp>

namespace cenpy::common::persistence::preferences::serializer
{
    std::string XmlSerializer::getExtension() const
    {
        return "xml";
    }

    pugi::xml_node PropertyToXml(const Property &property, pugi::xml_document &doc)
    {
        pugi::xml_node xmlProperty = doc.append_child("property");
        xmlProperty.append_attribute("key").set_value(property.getKey().c_str());

        // Assuming Property class has a stream insertion operator implemented
        std::ostringstream valueStream;
        valueStream << property;
        xmlProperty.append_child("value").text().set(valueStream.str().c_str());

        return xmlProperty;
    }

    void XmlToProperty(const pugi::xml_node &xmlProperty, Property &property)
    {
        property.read(xmlProperty.child_value("value"));
    }

    pugi::xml_node SectionToXml(const Section &section, pugi::xml_document &doc)
    {
        pugi::xml_node xmlSection = doc.append_child("section");
        xmlSection.append_attribute("name").set_value(section.getName().c_str());

        for (const auto &key : section.getKeys())
        {
            PropertyToXml(*section.getProperty(key), doc);
        }

        return xmlSection;
    }

    void XmlToSection(const pugi::xml_node &xmlSection, Section &section)
    {
        for (const auto &xmlProperty : xmlSection.children("property"))
        {
            std::shared_ptr<Property> property = section.getProperty(xmlProperty.attribute("key").value());
            XmlToProperty(xmlProperty, *property);
        }
    }

    void XmlSerializer::serialize(std::ostream &os, const Property &property) const
    {
        pugi::xml_document doc;
        PropertyToXml(property, doc);
        doc.save(os);
        os << "\n";
    }

    void XmlSerializer::deserialize(std::istream &is, Property &property) const
    {
        pugi::xml_document doc;
        doc.load(is);
        XmlToProperty(doc.child("property"), property);
    }

    void XmlSerializer::serialize(std::ostream &os, const Section &section) const
    {
        pugi::xml_document doc;
        SectionToXml(section, doc);
        doc.save(os);
        os << "\n";
    }

    void XmlSerializer::deserialize(std::istream &is, Section &section) const
    {
        pugi::xml_document doc;
        doc.load(is);
        XmlToSection(doc.child("section"), section);
    }

    void XmlSerializer::serialize(std::ostream &os, const Preferences &preferences) const
    {
        pugi::xml_document doc;
        doc.append_child("preferences");

        for (const auto &sectionName : preferences.getSections())
        {
            SectionToXml(preferences.getSection(sectionName), doc);
        }

        doc.save(os);
        os << "\n";
    }

    void XmlSerializer::deserialize(std::istream &is, Preferences &preferences) const
    {
        pugi::xml_document doc;
        doc.load(is);

        for (const auto &xmlSection : doc.child("preferences").children("section"))
        {
            Section section(xmlSection.attribute("name").value());
            XmlToSection(xmlSection, section);
            preferences.addSection(section);
        }
    }

} // namespace cenpy::common::persistence::preferences::serializer
