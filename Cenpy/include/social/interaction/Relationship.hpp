#pragma once

#include <vector>
#include <social/interaction/Conflict.hpp>

class Relationship
{
public:
    Relationship(int trustLevel, int affectionLevel);

    // Add getters and setters for individual attributes if needed

    void addConflict(const Conflict &conflict);

    std::string toString() const;

private:
    int trustLevel;
    int affectionLevel;
    std::vector<Conflict> conflicts;
};
