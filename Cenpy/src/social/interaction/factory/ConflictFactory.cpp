#include <social/interaction/factory/ConflictFactory.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Conflict ConflictFactory::createConflict(const std::string& name) {
    try {
        std::ifstream jsonFile("game/resources/assets/social/conflict/" + name + ".json");
        if (!jsonFile.is_open()) {
            throw std::runtime_error("Error opening JSON file");
        }
        nlohmann::json conflictData;
        jsonFile >> conflictData;

        return Conflict(
            conflictData["name"],
            conflictData["description"],
            conflictData["weight"]
        );
    } catch (const std::exception& e) {
        throw std::invalid_argument("Error loading character from JSON: " + std::string(e.what()));
    }
}
