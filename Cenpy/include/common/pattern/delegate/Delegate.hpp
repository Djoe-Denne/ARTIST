#pragma once

#include <optional>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <common/macros.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::common::pattern::delegate
{

    template <typename T>
    class ClassDelegate;

    /**
     * @class MethodDelegateBase
     * @brief Base class for method delegates.
     *
     * This class provides a base implementation for method delegates.
     * Method delegates are used to store and invoke methods with a specific signature.
     * It supports setting instance and class-level delegates, as well as before and after function hooks.
     */
    class MethodDelegateBase
    {
    public:
        using HookType = void (*)(...);

        /**
         * @brief Set the instance for the method delegate.
         *
         * @param instance The instance to set.
         */
        virtual void setInstance(std::any instance) = 0;

        /**
         * @brief Set the class-level delegate for the method delegate.
         *
         * @param classLevelDelegate The class-level delegate to set.
         */
        virtual void setClassLevelDelegate(std::any classLevelDelegate) = 0;

        /**
         * @brief Set the before function hook.
         *
         * @param beforeFunc The before function hook to set.
         */
        void setBeforeFunc(const HookType &beforeFunc)
        {
            m_beforeFunc = beforeFunc;
        }

        /**
         * @brief Set the after function hook.
         *
         * @param afterFunc The after function hook to set.
         */
        void setAfterFunc(const HookType &afterFunc)
        {
            m_afterFunc = afterFunc;
        }

        virtual ~MethodDelegateBase() {}

    private:
        std::optional<HookType> m_beforeFunc; /**< Optional before function hook. */
        std::optional<HookType> m_afterFunc;  /**< Optional after function hook. */

    protected:
        /**
         * @brief Constructor for MethodDelegateBase.
         *
         * @param beforeFunc The before function hook.
         * @param afterFunc The after function hook.
         */
        MethodDelegateBase(HookType beforeFunc = nullptr, HookType afterFunc = nullptr)
            : m_beforeFunc(beforeFunc), m_afterFunc(afterFunc) {}

        /**
         * @brief Execute the before function hook.
         *
         * @tparam T The type of the instance.
         * @param it The instance to pass to the before function hook.
         */
        template <typename T>
        void executeBeforeFunc(T *it)
        {
            if (m_beforeFunc && *m_beforeFunc)
            {
                (*m_beforeFunc)(it);
            }
        }

        /**
         * @brief Execute the after function hook.
         *
         * @tparam T The type of the instance.
         * @param it The instance to pass to the after function hook.
         */
        template <typename T>
        void executeAfterFunc(T *it)
        {
            if (m_afterFunc && *m_afterFunc)
            {
                (*m_afterFunc)(it);
            }
        }
    };

    template <typename R, typename T, typename... Args>
    /**
     * @brief Represents a method delegate that can be used to invoke a member function of a class.
     *
     * This class is derived from MethodDelegateBase and provides functionality to invoke a member function
     * with the specified arguments. It also supports hooks that can be executed before and after the invocation.
     *
     * @tparam T The class type that contains the member function.
     * @tparam R The return type of the member function.
     * @tparam Args The argument types of the member function.
     */
    class MethodDelegate : public MethodDelegateBase
    {
    private:
        std::shared_ptr<T> m_instance;          // Shared pointer to the instance of the class
        using MethodType = R (T::*)(Args...);   // Pointer to the member function type
        MethodType m_method;                    // Pointer to the member function
        ClassDelegate<T> *m_classLevelDelegate; // Pointer to the class-level delegate

    public:
        /**
         * @brief Constructs a MethodDelegate object.
         *
         * @param method Pointer to the member function.
         * @param beforeFunc Optional hook function to be executed before invoking the member function.
         * @param afterFunc Optional hook function to be executed after invoking the member function.
         */
        MethodDelegate(MethodType method, HookType beforeFunc = nullptr, HookType afterFunc = nullptr)
            : MethodDelegateBase(beforeFunc, afterFunc), m_method(method), m_classLevelDelegate() {}

        /**
         * @brief Destructor for the MethodDelegate.
         */
        virtual ~MethodDelegate() = default;

        /**
         * @brief Invokes the member function represented by the delegate.
         *
         * If the instance is not set, a runtime_error exception is thrown.
         * The beforeFunc hook function is executed before invoking the member function.
         * If the return type is void, the member function is called and the afterFunc hook function is executed.
         * If the return type is not void, the member function is called and the result is returned after executing the afterFunc hook function.
         *
         * @param args The arguments to be passed to the member function.
         * @return The result of the member function, if the return type is not void.
         */
        R operator()(Args... args)
        {
            if (!m_instance)
            {
                throw exception::TraceableException<std::runtime_error>("Instance not set");
            }

            executeBeforeFunc(this->m_classLevelDelegate);

            if constexpr (std::is_void<R>::value)
            {
                (m_instance.get()->*m_method)(args...);
                executeAfterFunc(this->m_classLevelDelegate);
                return;
            }
            else
            {
                R result = (m_instance.get()->*m_method)(args...);
                executeAfterFunc(this->m_classLevelDelegate);
                return result;
            }
        }

        /**
         * @brief Sets the class-level delegate for the MethodDelegate.
         *
         * @param classLevelDelegate The class-level delegate to be set.
         */
        void setClassLevelDelegate(std::any classLevelDelegate) override
        {
            m_classLevelDelegate = std::any_cast<ClassDelegate<T> *>(classLevelDelegate);
        }

        /**
         * @brief Sets the instance for the MethodDelegate.
         *
         * @param instance The instance to be set.
         */
        void setInstance(std::any instance) override
        {
            m_instance = std::any_cast<std::shared_ptr<T>>(instance);
        }

    protected:
        friend class ClassDelegate<T>;
    };

    /**
     * @brief A class template for creating class-level delegates.
     *
     * This template class allows the creation of delegates that can be used to invoke methods on a specific instance of a class.
     * It provides a convenient way to manage multiple method delegates and their associated hooks.
     *
     * @tparam T The class type on which the delegates will be invoked.
     */
    template <typename T>
    class ClassDelegate
    {
    public:
        /**
         * @brief Destroys the ClassDelegate object.
         *
         * Deletes all the method delegates associated with this ClassDelegate.
         */
        virtual ~ClassDelegate()
        {
            for (const auto &pair : m_methods)
            {
                delete pair.second;
            }
        }

    private:
        std::shared_ptr<T> m_instance;                         // The instance of the class on which the delegates will be invoked.
        std::map<std::string, MethodDelegateBase *> m_methods; // A map of method delegates associated with their names.
        typename MethodDelegateBase::HookType m_beforeFunc;    // The hook function to be executed before invoking a method delegate.
        typename MethodDelegateBase::HookType m_afterFunc;     // The hook function to be executed after invoking a method delegate.

    protected:
        /**
         * @brief Constructs a ClassDelegate object.
         *
         * @param instance The instance of the class on which the delegates will be invoked.
         * @param methods An initializer list of method delegates and their associated names.
         * @param beforeFunc The hook function to be executed before invoking a method delegate.
         * @param afterFunc The hook function to be executed after invoking a method delegate.
         */
        ClassDelegate(std::shared_ptr<T> instance, std::initializer_list<std::pair<std::string, MethodDelegateBase *>> methods, typename MethodDelegateBase::HookType beforeFunc = nullptr, typename MethodDelegateBase::HookType afterFunc = nullptr)
            : m_instance(instance), m_beforeFunc(beforeFunc), m_afterFunc(afterFunc)
        {
            for (const auto &pair : methods)
            {
                m_methods[pair.first] = pair.second;
            }
            for (const auto &pair : m_methods)
            {
                m_methods[pair.first]->setBeforeFunc(beforeFunc);
                m_methods[pair.first]->setAfterFunc(afterFunc);
                m_methods[pair.first]->setClassLevelDelegate(this);
                m_methods[pair.first]->setInstance(m_instance);
            }
        }

        /**
         * @brief Gets the instance of the class on which the delegates will be invoked.
         *
         * @return A reference to the instance of the class.
         */
        std::shared_ptr<T> &getInstance()
        {
            return m_instance;
        }

        /**
         * Retrieves the method delegate with the specified name.
         *
         * @param name The name of the method delegate.
         * @return A pointer to the MethodDelegateBase object.
         */
        MethodDelegateBase *getMethod(const std::string &name)
        {
            return m_methods[name];
        }
    };

/**
 * @def METHOD_IMPLEMENTATION(T, METHOD)
 * @brief Generates a method implementation that delegates the call to a ClassDelegate.
 * @param T The class type.
 * @param METHOD The method to be implemented.
 */
#define METHOD_IMPLEMENTATION(T, METHOD)                                                                                                                                                                                      \
    template <typename... Args>                                                                                                                                                                                               \
    auto METHOD(Args... args)                                                                                                                                                                                                 \
        -> decltype(cenpy::common::pattern::delegate::ClassDelegate<T>::getInstance()->METHOD(args...))                                                                                                                       \
    {                                                                                                                                                                                                                         \
        auto methodDelegate = dynamic_cast<cenpy::common::pattern::delegate::MethodDelegate<decltype(cenpy::common::pattern::delegate::ClassDelegate<T>::getInstance()->METHOD(args...)), T, Args...> *>(getMethod(#METHOD)); \
        return (*methodDelegate)(args...);                                                                                                                                                                                    \
    }
} // namespace cenpy::common::pattern::delegate

/**
 * @def CLASS_DELEGATE(T, BEFORE, AFTER, ...)
 * @brief Macro for creating a class delegate with before and after hooks.
 * @param T The class type.
 * @param BEFORE A function pointer to be called before each delegated method.
 * @param AFTER A function pointer to be called after each delegated method.
 * @param ... List of MethodDelegate instances representing methods to be delegated.
 */
#define DELEGATE(T, BEFORE, AFTER, ...)                                                                                                                                                               \
    class T##Delegate : public cenpy::common::pattern::delegate::ClassDelegate<T>                                                                                                                     \
    {                                                                                                                                                                                                 \
    public:                                                                                                                                                                                           \
        T##Delegate(std::shared_ptr<T> instance)                                                                                                                                                      \
            : cenpy::common::pattern::delegate::ClassDelegate<T>(instance, {NAMED_METHOD_PAIR(T, __VA_ARGS__)}, BEFORE, AFTER) {}                                                                     \
        T##Delegate(std::shared_ptr<T> instance, cenpy::common::pattern::delegate::MethodDelegateBase::HookType beforeFunc, cenpy::common::pattern::delegate::MethodDelegateBase::HookType afterFunc) \
            : cenpy::common::pattern::delegate::ClassDelegate<T>(instance, {NAMED_METHOD_PAIR(T, __VA_ARGS__)}, beforeFunc, afterFunc) {}                                                             \
        ~T##Delegate() {}                                                                                                                                                                             \
                                                                                                                                                                                                      \
        METHOD_IMPLEMENTATIONS(T, __VA_ARGS__)                                                                                                                                                        \
    };

#define NAMED_METHOD_PAIR(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_2(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_2(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_3(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_3(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_4(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_4(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_5(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_5(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_6(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_6(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_7(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_7(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_8(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_8(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_9(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_9(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_10(T, __VA_ARGS__))

#define NAMED_METHOD_PAIR_10(T, METHOD, ...) \
    {#METHOD, new cenpy::common::pattern::delegate::MethodDelegate(&T::METHOD)} __VA_OPT__(COMMA NAMED_METHOD_PAIR_11(T, __VA_ARGS__))

/**
 * @def EXPAND_VARIADIC(MACRO, ...)
 * @brief Macro for expanding a variadic argument list and applying a given macro.
 * @param MACRO The macro to apply to each argument.
 * @param ... The variadic arguments to expand.
 */
#define METHOD_IMPLEMENTATIONS(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_2(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_2(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_3(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_3(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_4(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_4(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_5(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_5(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_6(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_6(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_7(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_7(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_8(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_8(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_9(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_9(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_10(T, __VA_ARGS__))
#define METHOD_IMPLEMENTATIONS_10(T, METHOD, ...) METHOD_IMPLEMENTATION(T, METHOD) __VA_OPT__(METHOD_IMPLEMENTATIONS_11(T, __VA_ARGS__))
