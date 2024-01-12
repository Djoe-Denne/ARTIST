#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <graphic/context/ProgramContext.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/program/User.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::program
{
    template <typename API>
    class MockUser : public cenpy::graphic::shader::component::program::IProgramUser<API>
    {
    public:
        MOCK_METHOD(void, useProgram, (std::shared_ptr<typename API::ProgramContext> context), (override));
    };
}
