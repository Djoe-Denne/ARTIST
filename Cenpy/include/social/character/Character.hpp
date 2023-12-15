#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <utils.hpp>
#include <social/character/Personality.hpp>
#include <social/interaction/Relationship.hpp>

namespace cenpy::social::character
{
    class Character
    {
    private:
        std::string name;
        int age;
        std::string origin;
        bool sex;
        Personality personality;
        std::string displayable;
        std::unordered_map<std::string, std::shared_ptr<Relationship>, collection_utils::StringHash, collection_utils::StringEqual> relationships;

    public:
        Character(const std::string &name, int age, const std::string &origin, bool sex, const Personality &personality);

        [[nodiscard]] const std::string &getName() const;
        void setName(const std::string_view &value);
        [[nodiscard]] const int &getAge() const;
        void setAge(const int &value);
        [[nodiscard]] const std::string &getOrigin() const;
        [[nodiscard]] const bool &getSex() const;
        [[nodiscard]] const Personality &getPersonality() const;
        [[nodiscard]] std::string getType() const;
        [[nodiscard]] const std::string &getDisplayable() const;
        [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<Relationship>, collection_utils::StringHash, collection_utils::StringEqual> &getRelationships() const;

        void addRelationship(const std::string &characterName, const std::shared_ptr<Relationship> &relationship);

        template <typename T>
        void setMood(const T &trigger);

        [[noreturn]] void say(const std::string_view &text) const;

        [[nodiscard]] std::string toString() const;
    };
} // namespace cenpy::social::character
