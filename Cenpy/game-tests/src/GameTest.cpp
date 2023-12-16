#include <iostream>
#include <common/exception/TraceableException.hpp>
#include <manager/GameManager.hpp>
#include <graphic/shader/Shader.hpp>

int main()
{
    cenpy::manager::GameManager gameManager;
    try
    {
        gameManager.startMainLoop();
    }
    catch (const cenpy::common::exception::TraceableException<std::exception> &e)
    {
        std::cerr << e.what() << '\n';
#if __cplusplus > 202002L && _GLIBCXX_HAVE_STACKTRACE
        std::cerr << e.getStackTrace() << '\n';
#endif
        return 1;
    }
    return 0;
}
