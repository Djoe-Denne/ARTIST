#pragma once

#include <vector>
#include <ranges>
#include <common/pattern/observer/Observer.hpp>
#include <common/pattern/delegate/Delegate.hpp>

/**
 * @def SUBJECT(T, ...)
 * @brief Macro for creating a subject class with observer pattern support.
 * @param T The class type.
 * @param ... List of MethodDelegate instances representing methods to be delegated.
 */
#define SUBJECT(T, ...)                                                                                                                                        \
    DELEGATE(                                                                                                                                                  \
        T, nullptr, nullptr, __VA_ARGS__)                                                                                                                      \
    class T##Subject : public T##Delegate, public cenpy::common::pattern::observer::Subject<T>                                                                 \
    {                                                                                                                                                          \
    public:                                                                                                                                                    \
        T##Subject(std::shared_ptr<T> instance)                                                                                                                \
            : cenpy::common::pattern::observer::Subject<T>(), T##Delegate(instance,                                                                            \
                                                                          nullptr,                                                                             \
                                                                          cenpy::common::pattern::delegate::MethodDelegateBase::HookType(&notifyObserversFor)) \
        {                                                                                                                                                      \
            T##Delegate::bind(this);                                                                                                                           \
        }                                                                                                                                                      \
        static void notifyObserversFor(std::any it)                                                                                                            \
        {                                                                                                                                                      \
            std::any_cast<FakeClassSubject *>(it)->notifyObservers();                                                                                          \
        }                                                                                                                                                      \
        void notifyObservers() override                                                                                                                        \
        {                                                                                                                                                      \
            for (const auto &observer : cenpy::common::pattern::observer::Subject<T>::getObservers())                                                          \
            {                                                                                                                                                  \
                observer->update(*T##Delegate::getInstance());                                                                                                 \
            }                                                                                                                                                  \
        }                                                                                                                                                      \
    };

namespace cenpy::common::pattern::observer
{
    /**
     * @brief Subject interface
     * A Subject is an object that wishes to notify other objects about changes in its state.
     */
    template <typename T>
    class Subject
    {
    public:
        /**
         * @brief Adds an observer to the subject.
         *
         * @param observer A pointer to the observer to be added.
         */
        void addObserver(std::shared_ptr<Observer<T>> observer)
        {
            observers.push_back(observer);
        }

        /**
         * @brief Removes an observer from the subject.
         *
         * @param observer The observer to be removed.
         */
        void removeObserver(std::shared_ptr<Observer<T>> observer)
        {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }

        /**
         * Notifies all the observers with the given data.
         *
         */
        virtual void notifyObservers() = 0;

    protected:
        std::vector<std::shared_ptr<Observer<T>>> &getObservers()
        {
            return observers;
        }

    private:
        std::vector<std::shared_ptr<Observer<T>>> observers;
    };

} // namespace cenpy::common::pattern::observer
