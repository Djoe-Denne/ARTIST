#include <social/character/Character.hpp>
#include <iostream>
#include <format>

namespace csc = cenpy::social::character;

csc::Character::Character(const std::string &name, int age, const std::string &origin, bool sex, const csc::Personality &personality)
    : name(name), age(age), origin(origin), sex(sex), personality(personality) {}

const std::string &csc::Character::getName() const
{
    return name;
}

void csc::Character::setName(const std::string_view &value)
{
    name = value;
}

const int &csc::Character::getAge() const
{
    return age;
}

void csc::Character::setAge(const int &value)
{
    age = value;
}

const std::string &csc::Character::getOrigin() const
{
    return origin;
}

const bool &csc::Character::getSex() const
{
    return sex;
}

const csc::Personality &csc::Character::getPersonality() const
{
    return personality;
}

std::string csc::Character::getType() const
{
    return "character";
}

const std::string &csc::Character::getDisplayable() const
{
    return name; //+ "/" + mood.getState();
}

const std::unordered_map<std::string, std::shared_ptr<Relationship>, cenpy::collection_utils::StringHash, cenpy::collection_utils::StringEqual> &csc::Character::getRelationships() const
{
    return relationships;
}

void csc::Character::addRelationship(const std::string &characterName, const std::shared_ptr<Relationship> &relationship)
{
    relationships[characterName] = relationship;
}

void csc::Character::say(const std::string_view &text) const
{
    throw std::logic_error("The method or operation is not implemented. sentence: " + std::string(text) + "");
}

std::string csc::Character::toString() const
{
    return std::format("");
}
