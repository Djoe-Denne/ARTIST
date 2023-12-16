#pragma once

#include <string>
#include <regex>
#include <common/persistence/preferences/PreferencesCommon.hpp>

namespace cenpy::common::persistence::preferences
{

    /**
     * @brief The base class for property validators.
     *
     * This class provides an interface for validating property values.
     * Subclasses should implement the `isValid` method to define the validation logic.
     */
    class PropertyValidator
    {
    public:
        /**
         * @brief Checks if the given value is valid.
         *
         * @param value The value to be validated.
         * @return true if the value is valid, false otherwise.
         */
        virtual bool isValid(const std::any &value) const { return true; }

        /**
         * @brief Destructor.
         */
        virtual ~PropertyValidator() = default;
    };

    // a validator for string properties
    class RegexPropertyValidator : public PropertyValidator
    {
    public:
        explicit RegexPropertyValidator(const std::string &regex)
            : m_regex(regex)
        {
        }

        bool isValid(const std::any &value) const override
        {
            return std::regex_match(std::any_cast<std::string>(value), m_regex);
        }

    private:
        std::regex m_regex;
    };

    template <typename T>
    // a validator for comparable properties using borders values
    /**
     * @brief A validator that checks if a value is within a specified range.
     *
     * The BetweenPropertyValidator class is used to validate whether a value falls within a specified range.
     * It compares the value against a minimum and maximum value, and optionally includes or excludes the bounds.
     */
    class BetweenPropertyValidator : public PropertyValidator
    {
    public:
        /**
         * @brief Constructs a BetweenPropertyValidator object with the specified range and bounds.
         *
         * @param min The minimum value of the range.
         * @param max The maximum value of the range.
         * @param includeLowerBound Specifies whether the lower bound is included in the range.
         * @param includeUpperBound Specifies whether the upper bound is included in the range.
         */
        BetweenPropertyValidator(const T &min, const T &max, const bool &includeLowerBound, const bool &includeUpperBound)
            : m_min(min), m_max(max), m_includeLowerBound(includeLowerBound), m_includeUpperBound(includeUpperBound)
        {
        }

        /**
         * @brief Checks if the given value is within the specified range.
         *
         * @param value The value to be validated.
         * @return true if the value is within the range, false otherwise.
         */
        bool isValid(const std::any &value) const override
        {
            T value_ = std::any_cast<T>(value);
            return (m_includeLowerBound ? value_ >= m_min : value_ > m_min) && (m_includeUpperBound ? value_ <= m_max : value_ < m_max);
        }

    private:
        T m_min;                  ///< The minimum value of the range.
        T m_max;                  ///< The maximum value of the range.
        bool m_includeLowerBound; ///< Specifies whether the lower bound is included in the range.
        bool m_includeUpperBound; ///< Specifies whether the upper bound is included in the range.
    };

    // A validator for string properties

}