#pragma once

namespace cenpy::component
{

    /**
     * @brief The base class for all components.
     *
     * This class provides a common interface for all components in the system.
     *
     * It is an abstract class and should be inherited by concrete component classes.
     */
    class Component
    {
    public:
        virtual ~Component() = default;
    };
} // namespace cenpy::component
