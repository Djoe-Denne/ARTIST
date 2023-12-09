# Cen'py Game Engine Coding Guidelines

## General Guidelines

- Use meaningful names for variables, functions, and classes. Aim for clarity and readability.
- Follow a consistent naming convention, such as CamelCase for class names and snake_case for function and variable names.
- Organize code logically into namespaces and classes to maintain a clean and modular structure.
- Include comments to explain complex logic, especially in cases where the code might be non-intuitive to others.

## Header Files

- Use `#pragma once` for header file guards to prevent multiple inclusions.
- Include necessary headers and dependencies in each header file.
- Arrange includes in alphabetical order and group them logically.
- Prefere forward declaratin when possible

```cpp
#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <common/exception/TraceableException.hpp>
#include <common/persistence/preferences/PreferencesCommon.hpp>
#include <common/persistence/preferences/PropertyValidators.hpp>
#include <common/persistence/preferences/serializer/IniSerializer.hpp>
```

## Namespace

- Use namespaces to logically group related classes and functions.
- Provide a brief description of the namespace's purpose in comments.

```cpp
namespace cenpy::common::persistence::preferences
{
    // ... (namespace content)
}
```

## Classes

- Begin class declarations with a brief comment describing the purpose of the class.
- Follow the Rule of Three/Five/Zero for custom resource management classes (provide destructor, copy/move constructors, and assignment operators as needed).
- Group public, protected, and private sections logically.


## Member Functions

- Begin function definitions with a brief comment describing the purpose of the function.
- Use consistent indentation and formatting.
- Group related functions together.
- use `[[nodiscard]]` when youb fill it's needed

## Templated Code

- Provide comments explaining template parameters and their significance.


## Exception Handling

- Use exception handling judiciously, providing informative error messages.
- Use specific exception types rather than generic ones when possible.
- Use `TraceableException` for better debugging

```cpp
if (propertyValue)
{
    return std::dynamic_pointer_cast<T>(propertyValue);
}
else
{
    throw exception::TraceableException<std::runtime_error>("Invalid property value");
}
```

## Code Formatting

- Use consistent code formatting throughout the project.
- Consider using an automatic code formatter to maintain consistency.

## Testing

- Include unit tests for critical functions and classes.
- Use Google Test for comprehensive testing.

## Documentation
CONTRIBUTING
- Follow the contributing guidelines outlined in [Contribution Guidelines](CONTRIBUTING.md).

By adhering to these coding guidelines, you contribute to creating a clean, maintainable, and collaborative codebase for Cen'py Game Engine.

