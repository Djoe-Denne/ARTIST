# Preferences Library
 Overview

The Preferences library is a C++ implementation for managing application preferences using an INI file format. It allows developers to define preference sections and properties with default values, ensuring the creation of the file with specified defaults if it doesn't exist. The library provides a convenient way to read, write, and validate preferences.

## File Format

Preferences are stored in several predefined format has:

- INI

```ini
[section]
key=value
[section2]
key2=value2
```

- JSON

```json
{
    "section": {
        "key": "value"
    },
    "section2": {
        "key2": "value2"
    }
}
```

The file location varies depending on the platform:

- Windows: `%APPDATA%/<appname>/<filename>`
- Linux: `~/.config/<appname>/<filename>`
- MacOS: `~/Library/Application Support/<appname>/<filename>`
- Android: `/data/data/<appname>/<filename>`

## Usage

To use the Preferences library, follow these steps:

1. Include the necessary headers:

```cpp
#include <common/persistence/preferences/Preferences.hpp>
```

2. Create an instance of the `Preferences` class, specifying the application name and file name:

```cpp
Preferences preferences("appname", "filename");
```

3. Define preference sections and properties with default values:

```cpp
Section section("section");
section.createProperty("key", 1, std::make_unique<PropertyBetweenValidator>(1, 99));
section.createProperty("key2", "something", std::make_unique<PropertyRegexValidator>("[a-z]+"));
section.createProperty("key3", true);
section.createProperty("key4", ResolutionPropertyValue(800, 600));
preferences.setSection("section", section);
```

4. Load preferences from the file:

```cpp
preferences.load();
```

   This will load preferences from the file, creating it with default values if it doesn't exist.

5. Access and modify preferences:

```cpp
int value = preferences.get<int>("section", "key");
preferences.set("section", "key", newValue);
```

6. Save preferences to the file:

```cpp
preferences.save();
```

## Property Types

The library supports various property types, including `int`, `double`, `std::string`, `bool`, and custom types derived from `PropertyValue`. Developers can also define custom property validators.

## Validation

Preferences can be validated using built-in or custom validators. Validators include `PropertyBetweenValidator` for range validation and `PropertyRegexValidator` for string pattern validation.

## Platform-Specific Paths

The library automatically determines the appropriate path for storing the preferences file based on the platform.

## What's next ?

* Multi level section. Some storage format like Yaml or Json allow in-depth structure. The idea is to implement it on Serializer side. So that it could be declare as sections:

```cpp
Section section("section.subsection");
Section section2("section.other-subsection");
```

* Rework Yaml ad XML serializer, I did them quickly and I'm not at all satisfied with them
