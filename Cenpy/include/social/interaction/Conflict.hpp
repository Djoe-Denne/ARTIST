#pragma once

#include <vector>
#include <string>
#include <social/interaction/Resolution.hpp>

class Conflict
{
public:
    Conflict(const std::string &name, const std::string &description, int weight);

    void addResolution(const Resolution &resolution);

    // Add getters for individual attributes if needed
    std::string getName() const;

private:
    std::string name;
    std::string imagePath;
    std::string description;
    int weight;
    std::vector<Resolution> resolutions;
};
