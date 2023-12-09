#pragma once

#include <string>

class Resolution {
public:
    Resolution(const std::string& name, const std::string& description, bool achieved = false);

    // Add any necessary public methods or members

private:
    std::string name;
    std::string image_path;
    std::string description;
    bool achieved;
};
