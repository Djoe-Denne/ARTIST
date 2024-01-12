#pragma once
#include <gtest/gtest.h>
#include <functional>
#include <exception>
#include <string>

namespace cenpy::test::utils
{
    // Custom matcher for exception messages
    template <typename ExceptionType>
    void expectSpecificError(const std::function<void()> &func, const ExceptionType &expectedException)
    {
        try
        {
            func();
            FAIL() << "Expected an exception to be thrown";
        }
        catch (const ExceptionType &e)
        {
            std::string errorMsg = e.what();
            EXPECT_NE(errorMsg.find(expectedException.what()), std::string::npos);
        }
        catch (...)
        {
            FAIL() << "Expected std::runtime_error to be thrown";
        }
    }
}