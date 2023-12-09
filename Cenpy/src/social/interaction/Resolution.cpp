#include <social/interaction/Resolution.hpp>

Resolution::Resolution(const std::string& name, const std::string& description, bool achieved)
    : name(name), description(description), achieved(achieved) {
    image_path = "social/resolution/" + name;
    // Add any additional initialization logic if needed
}
