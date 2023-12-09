#include <social/interaction/Conflict.hpp>

Conflict::Conflict(const std::string& name, const std::string& description, int weight)
    : name(name), imagePath("social/conflict/" + name), description(description), weight(weight) {
    // Constructor implementation
    // You can add validation or other logic if needed
}

void Conflict::addResolution(const Resolution& resolution) {
    // Add a possible resolution to the list of resolutions
    resolutions.push_back(resolution);
}

std::string Conflict::getName() const {
    // Return the name of the conflict
    return name;
}