#include <filesystem>
#include <common/persistence/preferences/serializer/Serializer.hpp>
#include <common/persistence/preferences/Preferences.hpp>

namespace cenpy::common::persistence::preferences::serializer
{

    std::string getAppDataPath()
    {
#ifdef __mock_appdata__
        return ".";
#elif defined(OS_WINDOWS)
        return std::getenv("APPDATA");
#elif defined(OS_LINUX) || defined(OS_MACOSX)
        return std::string(std::getenv("HOME")) + "/.config";
#elif defined(OS_ANDROID)
        // You need to adapt this to your specific needs on Android
        return "/data/data/com.yourapp.package";
#else
        // Default to the current directory for other platforms
        return ".";
#endif
    }

    bool Serializer::saveToFile(const Preferences &preferences) const
    {
        ensureSeriability(preferences);
        if (std::ofstream file(getPreferencesFilePath(preferences)); file.is_open())
        {
            serialize(file, preferences);
            file.close();
            return true;
        }
        return false;
    }

    bool Serializer::loadFromFile(Preferences &preferences) const
    {
        if (fileExists(preferences))
        {
            if (std::ifstream file(getPreferencesFilePath(preferences)); file.is_open())
            {
                deserialize(file, preferences);
                file.close();
                return true;
            }
        }
        saveToFile(preferences);
        return false;
    }

    void Serializer::ensureSeriability(const Preferences &preferences) const
    {
        std::filesystem::path path(getAppDir(preferences));
        if (!std::filesystem::exists(path))
        {
            std::filesystem::create_directories(path);
        }
    }

    bool Serializer::fileExists(const Preferences &preferences) const
    {
        std::filesystem::path path(getPreferencesFilePath(preferences));
        return std::filesystem::exists(path);
    }

    std::string Serializer::getAppDir(const Preferences &preferences) const
    {
        return getAppDataPath() + "/" + preferences.getAppName();
    }

    std::string Serializer::getPreferencesFilePath(const Preferences &preferences) const
    {
        return getAppDir(preferences) + "/" + preferences.getFilename() + "." + getExtension();
    }

    std::string Serializer::trim(const std::string &str) const
    {
        size_t first = str.find_first_not_of(" \t\r\n");
        size_t last = str.find_last_not_of(" \t\r\n");

        if (first == std::string::npos || last == std::string::npos)
        {
            return "";
        }

        return str.substr(first, last - first + 1);
    }
} // namespace cenpy::common::persistence::preferences::serializer
