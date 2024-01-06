#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <graphic/context/ProgramContext.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/program/Resetter.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::program
{
    class MockResetter : public cenpy::graphic::shader::component::program::IProgramResetter<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, resetProgram, (std::shared_ptr<typename graphic::api::MockOpenGL::ProgramContext> context), (override));
    };
}
