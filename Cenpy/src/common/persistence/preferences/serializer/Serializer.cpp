#include <filesystem>
#include <common/persistence/preferences/serializer/Serializer.hpp>
#include <common/persistence/preferences/Preferences.hpp>

namespace cenpy::common::persistence::preferences::serializer
{

    std::string getAppDataPath()
    {
#ifdef TEST
        return "./test/persistence/preferences";
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
        std::ofstream file(getFilename(preferences.getAppName(), preferences.getFilename()));
        if (file.is_open())
        {
            serialize(file, preferences);
            file.close();
            return true;
        }
        return false;
    }

    bool Serializer::loadFromFile(Preferences &preferences) const
    {
        std::string appname = preferences.getAppName();
        std::string filename = preferences.getFilename();
        if (fileExists(appname, filename))
        {
            std::ifstream file(getFilename(appname, filename));
            if (file.is_open())
            {
                deserialize(file, preferences);
                file.close();
                return true;
            }
        }
        saveToFile(preferences);
        return false;
    }

    bool Serializer::fileExists(const std::string &appname, const std::string &filename) const
    {
        std::filesystem::path filePath(getFilename(appname, filename));
        return std::filesystem::exists(filePath);
    }

    std::string Serializer::getFilename(const std::string &appname, const std::string &filename) const
    {
        return getAppDataPath() + "/" + appname + "/" + filename + "." + getExtension();
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
