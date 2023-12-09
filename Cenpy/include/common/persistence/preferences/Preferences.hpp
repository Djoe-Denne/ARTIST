#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <variant>
#include <common/exception/TraceableException.hpp>
#include <common/persistence/preferences/PreferencesCommon.hpp>
#include <common/persistence/preferences/PropertyValidators.hpp>
#include <common/persistence/preferences/serializer/IniSerializer.hpp>

/**
 * @brief Namespace for Preferences classes and functions
 * Preferences are stored in a file in the following INI format:
 * [section]
 * key=value
 * [section2]
 * key2=value2
 *
 * The location of the file depends on the platform:
 * - Windows: %APPDATA%/<appname>/<filename>
 * - Linux: ~/.config/<appname>/<filename>
 * - MacOS: ~/Library/Application Support/<appname>/<filename>
 * - Android: /data/data/<appname>/<filename>
 *
 * The game developper must define the Preference Sections and Properties with default value.
 * so that is the file doesn't exist it will be created with the default values.
 * The Preference structure must be defined to load a file, if you try to load a file with a different structure
 * or without a section or property that is defined in the structure, an exception will be thrown.
 * This allow to check properties value when loading them from the file.
 *
 * Example:
 * Preferences preferences("appname", "filename");
 * Section section("section");
 * section.createProperty("key", 1, std::make_unique<PropertyBetweenValidator>(1, 99));
 * section.createProperty("key2", "something", std::make_unique<PropertyRegexValidator>("[a-z]+"));
 * section.createProperty("key3", true);
 * section.createProperty("key4", ResolutionPropertyValue(800, 600));
 * preferences.setSection("section", section);
 *
 * preferences.load();
 */
namespace cenpy::common::persistence::preferences
{

    class PropertyValue
    {
    public:
        virtual ~PropertyValue() = default;

        // force implementation of the << and >> operators in child classes
        virtual void read(std::istream &is) = 0;
        virtual std::ostream &write(std::ostream &os) const = 0;

        friend std::ostream &operator<<(std::ostream &os, const PropertyValue &propertyValue)
        {
            return propertyValue.write(os);
        }

        friend std::istream &operator>>(std::istream &is, PropertyValue &propertyValue)
        {
            propertyValue.read(is);
            return is;
        }
    };

    // Templated Property class
    /**
     * @brief Represents a property with a key-value pair.
     *
     * The Property class provides methods to get and set the key and value of the property,
     * as well as check the validity of the value based on an optional validator.
     * It also supports serialization and deserialization to/from input/output streams.
     *
     * @tparam T The type of the value stored in the property.
     */
    class Property
    {
    public:
        template <PropertyVariantType T>
        /**
         * @brief Constructs a Property object with the specified key, value, and validator.
         *
         * @param key The key of the property.
         * @param value The value of the property.
         * @param validator The validator for the property value.
         */
        Property(const std::string &key, const T &value, std::unique_ptr<PropertyValidator> validator = nullptr)
            : m_key(key), m_validator(std::move(validator))
        {
            setValue(value);
        }

        /**
         * @brief Get the key associated with the preference.
         *
         * @return The key as a string.
         */
        [[nodiscard]] const std::string &getKey() const
        {
            return m_key;
        }

        template <PropertyVariantType T>
        /**
         * @brief Get the value of the preference.
         *
         * @return The value of the preference.
         */
        [[nodiscard]] auto getValue() const -> std::conditional_t<std::is_base_of_v<PropertyValue, T>, std::shared_ptr<T>, T>
        {
            if constexpr (std::is_base_of_v<PropertyValue, T>)
            {
                std::shared_ptr<PropertyValue> propertyValue = std::any_cast<std::shared_ptr<PropertyValue>>(m_value);
                if (propertyValue)
                {
                    return std::dynamic_pointer_cast<T>(propertyValue);
                }
                else
                {
                    throw exception::TraceableException<std::runtime_error>("Invalid property value");
                }
            }
            else
            {
                return std::any_cast<T>(m_value);
            }
        }

        template <PropertyVariantType T>
        /**
         * @brief Sets the value of the preference.
         *
         * @param value The value to be set.
         */
        void setValue(const T &value)
        {
            if ((m_validator) && !m_validator->isValid(value))
            {
                throw std::invalid_argument("Invalid value");
            }
            if constexpr (std::is_base_of_v<PropertyValue, T>)
            {
                std::shared_ptr<PropertyValue> propertyValue = std::make_shared<T>(value);
                m_value = propertyValue;
            }
            else
            {
                m_value = value;
            }
        }

        // Serialize the property to an output stream
        friend std::ostream &operator<<(std::ostream &os, const Property &property)
        {
            if (property.m_value.type() == typeid(int))
            {
                os << std::any_cast<int>(property.m_value);
            }
            else if (property.m_value.type() == typeid(double))
            {
                os << std::any_cast<double>(property.m_value);
            }
            else if (property.m_value.type() == typeid(std::string))
            {
                os << std::any_cast<std::string>(property.m_value);
            }
            else if (property.m_value.type() == typeid(bool))
            {
                os << (std::any_cast<bool>(property.m_value) ? "true" : "false");
            }
            else
            {
                auto propertyValue = std::any_cast<std::shared_ptr<PropertyValue>>(property.m_value);
                if (propertyValue)
                {
                    os << *propertyValue;
                }
                else
                {
                    throw exception::TraceableException<std::runtime_error>("Invalid property value");
                }
            }
            return os;
        }

        void read(const std::string &str)
        {
            if (m_value.type() == typeid(int))
            {
                setValue(std::stoi(str));
            }
            else if (m_value.type() == typeid(double))
            {
                setValue(std::stod(str));
            }
            else if (m_value.type() == typeid(std::string))
            {
                setValue(str);
            }
            else if (m_value.type() == typeid(bool))
            {
                setValue(str == "true");
            }
            else
            {
                auto propertyValue = std::any_cast<std::shared_ptr<PropertyValue>>(m_value);
                if (propertyValue)
                {
                    std::istringstream iss(str);
                    iss >> *propertyValue;
                }
                else
                {
                    throw exception::TraceableException<std::runtime_error>("Invalid property value");
                }
            }
        }

        void write(void *ptr) const
        {
            if (m_value.type() == typeid(int))
            {
                *static_cast<int *>(ptr) = std::any_cast<int>(m_value);
            }
            else if (m_value.type() == typeid(double))
            {
                *static_cast<double *>(ptr) = std::any_cast<double>(m_value);
            }
            else if (m_value.type() == typeid(std::string))
            {
                *static_cast<std::string *>(ptr) = std::any_cast<std::string>(m_value);
            }
            else if (m_value.type() == typeid(bool))
            {
                *static_cast<bool *>(ptr) = std::any_cast<bool>(m_value);
            }
            else
            {
                auto propertyValue = std::any_cast<std::shared_ptr<PropertyValue>>(m_value);
                if (propertyValue)
                {
                    std::ostringstream oss;
                    oss << *propertyValue;
                    *static_cast<std::string *>(ptr) = oss.str();
                }
                else
                {
                    throw exception::TraceableException<std::runtime_error>("Invalid property value");
                }
            }
        }

    private:
        std::string m_key;                              /**< The key of the property. */
        std::any m_value;                               /**< The value of the property. */
        std::unique_ptr<PropertyValidator> m_validator; /**< The validator for the property value. */

        friend class Section;
    };

    /**
     * @brief Represents a section in the preferences file.
     */
    class Section
    {
    public:
        /**
         * @brief Default constructor.
         */
        Section() = default;

        /**
         * @brief Constructor that sets the name of the section.
         * @param name The name of the section.
         */
        explicit Section(const std::string &name);

        /**
         * @brief Get the name of the section.
         * @return The name of the section.
         */
        [[nodiscard]] std::string getName() const;

        /**
         * @brief Create a property in the section.
         * @param key The key of the property.
         * @param value The value of the property.
         * @param validator An optional validator for the property.
         */
        template <PropertyVariantType T>
        void createProperty(const std::string &key, const T &value, std::unique_ptr<PropertyValidator> validator = nullptr)
        {
            m_properties[key] = std::make_shared<Property>(key, value, std::move(validator));
        }

        void createProperty(const std::string &key, const char *value, std::unique_ptr<PropertyValidator> validator = nullptr)
        {
            createProperty<std::string>(key, std::string(value), std::move(validator));
        }

        /**
         * @brief Get the value of a property.
         * @tparam T The type of the property value.
         * @param key The key of the property.
         * @return The value of the property.
         */
        template <typename T>
        [[nodiscard]] auto get(const std::string &key) const -> std::conditional_t<std::is_base_of_v<PropertyValue, T>, std::shared_ptr<T>, T>
        {
            return getProperty(key)->getValue<T>();
        }

        /**
         * @brief Get a property object.
         * @tparam T The type of the property value.
         * @param key The key of the property.
         * @return The property object.
         */
        [[nodiscard]] std::shared_ptr<Property> getProperty(const std::string &key) const;

        /**
         * @brief Get the keys of the properties in the section.
         * @return A vector containing the keys of the properties.
         */
        [[nodiscard]] std::vector<std::string> getKeys() const;

        /**
         * @brief Set the value of a property.
         * @tparam T The type of the property value.
         * @param key The key of the property.
         * @param value The new value of the property.
         */
        template <typename T>
        void set(const std::string &key, const T &value)
        {
            this->getProperty(key)->setValue<T>(value);
        }

        /**
         * @brief Check if a key is valid for the section.
         * @param key The key to check.
         * @return True if the key is valid, false otherwise.
         */
        [[nodiscard]] bool isValidKey(const std::string &key) const;

    private:
        std::string m_name;                                                      // The name of the section
        std::unordered_map<std::string, std::shared_ptr<Property>> m_properties; // The properties in the section
    };

    /**
     * @class Preferences
     * @brief Represents a set of preferences for an application.
     *
     * The Preferences class provides methods to store and retrieve key-value pairs
     * in different sections. It also supports serialization and deserialization
     * of preferences to and from a file.
     */
    class Preferences
    {
    public:
        /**
         * @brief Constructs a Preferences object with the specified application name and filename.
         *
         * @param appName The name of the application.
         * @param filename The name of the file to store the preferences.
         */
        Preferences(const std::string &appName, const std::string &filename, const std::shared_ptr<serializer::Serializer> &serializer = std::make_shared<serializer::IniSerializer>());

        /**
         * @brief Gets the value associated with a key in a specific section.
         *
         * @tparam T The type of the value to retrieve.
         * @param section The name of the section.
         * @param key The key of the value.
         * @param defaultValue The default value to return if the key is not found.
         * @return The value associated with the key, or the default value if the key is not found.
         */
        template <typename T>
        [[nodiscard]] auto get(const std::string &section, const std::string &key) const -> std::conditional_t<std::is_base_of_v<PropertyValue, T>, std::shared_ptr<T>, T>
        {
            auto it = m_sections.find(section);
            if (it != m_sections.end())
            {
                return it->second.get<T>(key);
            }
            throw exception::TraceableException<std::runtime_error>("Invalid section: " + section);
        }

        /**
         * @brief Sets the value associated with a key in a specific section.
         *
         * @tparam T The type of the value to set.
         * @param section The name of the section.
         * @param key The key of the value.
         * @param property The value to set.
         */
        template <typename T>
        void set(const std::string &section, const std::string &key, const T &value)
        {
            auto it = m_sections.find(section);
            if (it != m_sections.end())
            {
                it->second.set<T>(key, value);
            }
            else
            {
                throw exception::TraceableException<std::runtime_error>("Invalid section: " + section);
            }
        }

        /**
         * @brief Sets the section object for a specific section.
         *
         * @param sectionObject The Section object to set.
         */
        void addSection(const Section &sectionObject);

        /**
         * @brief Gets the section object for a specific section.
         *
         * @param section The name of the section.
         * @return The Section object for the specified section.
         */
        [[nodiscard]] const Section &getSection(const std::string &section) const;

        /**
         * @brief Gets the section object for a specific section.
         *
         * @param section The name of the section.
         * @return The Section object for the specified section.
         */
        [[nodiscard]] Section &getSection(const std::string &section);

        /**
         * @brief Gets the keys of the sections in the preferences.
         *
         * @return A vector containing the keys of the sections.
         */
        [[nodiscard]] std::vector<std::string> getSections() const;

        [[nodiscard]] const std::string &getFilename() const
        {
            return m_filename;
        }

        [[nodiscard]] const std::string &getAppName() const
        {
            return m_appName;
        }

        /**
         * @brief Saves the preferences to the file.
         */
        void save();

        /**
         * @brief Loads the preferences from the file.
         */
        bool load();

        /**
         * @brief Checks if the preferences file exists.
         *
         * @return True if the file exists, false otherwise.
         */
        bool fileExists() const;

    private:
        std::string m_appName;
        std::string m_filename;
        std::unordered_map<std::string, Section> m_sections;
        std::shared_ptr<serializer::Serializer> m_serializer;

        /**
         * @brief Loads the preferences from the file.
         *
         * @return True if the preferences were successfully loaded, false otherwise.
         */
        bool loadFromFile();

        /**
         * @brief Saves the preferences to the file.
         *
         * @return True if the preferences were successfully saved, false otherwise.
         */
        bool saveToFile() const;
    };
} // namespace preferences
