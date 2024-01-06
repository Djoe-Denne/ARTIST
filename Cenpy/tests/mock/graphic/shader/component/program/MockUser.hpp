#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <graphic/context/ProgramContext.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/program/User.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::program
{
    class MockUser : public cenpy::graphic::shader::component::program::IProgramUser<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, useProgram, (std::shared_ptr<typename graphic::api::MockOpenGL::ProgramContext> context), (override));
    };
}
