#pragma once

#include <string>
#include <unordered_map>
#include <memory>
// #include "MoodStateMachine.h"
#include <social/character/Personality.hpp>
#include <social/interaction/Relationship.hpp>
// #include "DisplayableContainer.h"
// #include "SceneObserver.h"

namespace cenpy::social::character
{
    class Character
    { //: public DisplayableContainer {
    private:
        std::string name;
        int age;
        std::string origin;
        bool sex;
        Personality personality;
        std::string displayable;
        std::unordered_map<std::string, std::shared_ptr<Relationship>> relationships;
        // MoodStateMachine mood;

    public:
        Character(const std::string &name, int age, const std::string &origin, bool sex, const Personality &personality);

        std::string getName() const;
        void setName(const std::string &value);
        int getAge() const;
        void setAge(int value);
        std::string getOrigin() const;
        bool getSex() const;
        Personality getPersonality() const;
        std::string getType() const;
        std::string getDisplayable() const;
        std::unordered_map<std::string, std::shared_ptr<Relationship>> getRelationships() const;
        // MoodStateMachine getMood() const;

        void addRelationship(const std::string &characterName, const std::shared_ptr<Relationship> &relationship);

        template <typename T>
        void setMood(const T &trigger);

        // RenPyCharacter getRenPyCharacter() const;

        void say(const std::string &text);

        std::string toString() const;
    };
} // namespace cenpy::social::character
