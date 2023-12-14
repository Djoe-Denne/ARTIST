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
        std::cerr << e.getStackTrace() << '\n';
        return 1;
    }
    return 0;
}
