#pragma once

namespace cenpy::common::pattern::observer
{

    /**
     * @brief Observer interface
     * An Observer is an object that wishes to be informed about events happening in the system.
     */
    template <typename T>
    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void update(const T &data) = 0;
    };

} // namespace cenpy::common::pattern::observer
