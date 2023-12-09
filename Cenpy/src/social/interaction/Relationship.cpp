#include <social/interaction/Relationship.hpp>

Relationship::Relationship(int trustLevel, int affectionLevel)
    : trustLevel(trustLevel), affectionLevel(affectionLevel) {
    // Constructor implementation
    // You can add validation or other logic if needed
}

void Relationship::addConflict(const Conflict& conflict) {
    // Add a conflict to the list of conflicts in the relationship
    conflicts.push_back(conflict);
}

std::string Relationship::toString() const {
    // Return a string representation of the relationship
    // You can modify this based on your requirements
    std::string result = "Trust Level: " + std::to_string(trustLevel) +
                         "\nAffection Level: " + std::to_string(affectionLevel) +
                         "\nConflicts: ";
    for (const auto& conflict : conflicts) {
        result += conflict.getName() + ", ";
    }
    return result;
}