#include <social/character/Character.hpp>
#include <iostream>

namespace csc = cenpy::social::character;

csc::Character::Character(const std::string &name, int age, const std::string &origin, bool sex, const csc::Personality &personality)
    : name(name), age(age), origin(origin), sex(sex), personality(personality), displayable(""), relationships() /*, mood(MoodStateMachine::createMoodStateMachine())*/ {}

std::string csc::Character::getName() const
{
    return name;
}

void csc::Character::setName(const std::string &value)
{
    name = value;
}

int csc::Character::getAge() const
{
    return age;
}

void csc::Character::setAge(int value)
{
    age = value;
}

std::string csc::Character::getOrigin() const
{
    return origin;
}

bool csc::Character::getSex() const
{
    return sex;
}

csc::Personality csc::Character::getPersonality() const
{
    return personality;
}

std::string csc::Character::getType() const
{
    return "character";
}

std::string csc::Character::getDisplayable() const
{
    return name; //+ "/" + mood.getState();
}

std::unordered_map<std::string, std::shared_ptr<Relationship>> csc::Character::getRelationships() const
{
    return relationships;
}

void csc::Character::addRelationship(const std::string &characterName, const std::shared_ptr<Relationship> &relationship)
{
    relationships[characterName] = relationship;
}

/*MoodStateMachine csc::Character::getMood() const {
    return mood;
}

template <typename T>
void csc::Character::setMood(const T& trigger) {
    mood.trigger(trigger);
}
/*
RenPyCharacter csc::Character::getRenPyCharacter() const {
    return RenPyCharacter(name);
}*/

void csc::Character::say(const std::string &text)
{
    // getRenPyCharacter()(text);
}

std::string csc::Character::toString() const
{
    return "Name: " /*+ name + "\nAge: " + std::to_string(age) + "\nOrigin: " + origin + "\nSex: " + (sex ? "Male" : "Female") + "\n"
        + "Personality: " + personality.toString() + "\nSprite Folder: " + spriteFolder + "\nRelationships: " + concatenateRelationships()*/
        ;
}
