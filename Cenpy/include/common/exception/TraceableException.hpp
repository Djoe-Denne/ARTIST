#pragma once

#include <string>
#include <iostream>
#if __cplusplus > 202002L && _GLIBCXX_HAVE_STACKTRACE
#include <stacktrace>
#endif
#include <stdexcept>

namespace cenpy::common::exception
{

    template <typename E>
        requires std::is_base_of_v<std::exception, E>
    class TraceableException : public E
    {
#if __cplusplus > 202002L && _GLIBCXX_HAVE_STACKTRACE
    public:
        explicit TraceableException(const std::string &what) : E(what)
        {
            stackTrace = std::stacktrace::current();
        }

        const std::stacktrace &getStackTrace() const
        {
            return stackTrace;
        }

        std::string getStackTraceString() const
        {
            return format_stacktrace(stackTrace);
        }

    private:
        std::stacktrace stackTrace;

        std::string format_stacktrace(const std::stacktrace &st)
        {
            std::ostringstream oss;
            for (const auto &entry : st)
            {
                oss << entry << '\n';
            }
            return oss.str();
        }
#else

    public:
        explicit TraceableException(const char *what) : E(what)
        {
        }

        const std::stacktrace &getStackTrace() const
        {
            return NULL;
        }

        const std::string &getStackTraceString() const
        {
            return "Stacktrace not available";
        }
#endif
    };

} // namespace cenpy::common::exception
