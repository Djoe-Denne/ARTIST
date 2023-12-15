#pragma once

#include <type_traits>
#include <memory>
#include <component/Component.hpp>

namespace cenpy::system
{
    template <typename T>
        requires std::is_base_of_v<component::Component, T>
    /**
     * @brief The System class represents a base class for system components.
     */
    class System
    {
    public:
        virtual ~System() = default;

        /**
         * @brief Updates the specified instance of the component.
         *
         * @param instance The weak pointer to the component instance.
         */
        virtual void update(std::weak_ptr<component::Component> instance)
        {
            update(std::dynamic_pointer_cast<T>(instance.lock()));
            m_updateNeeded = false;
        }

        /**
         * @brief Updates the specified instance of the component.
         *
         * @param instance The reference to the component instance.
         */
        virtual void update(T &instance) = 0;

        /**
         * @brief Checks if the system needs to be updated.
         *
         * @return true if the system needs to be updated, false otherwise.
         */
        [[nodiscard]] bool needsUpdate() const
        {
            return m_updateNeeded;
        }

        /**
         * @brief Sets the update flag to true.
         */
        void setUpdateNeeded()
        {
            m_updateNeeded = true;
        }

    private:
        bool m_updateNeeded;
    };
} // namespace system