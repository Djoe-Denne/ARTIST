#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <graphic/context/ProgramContext.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/program/Resetter.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::program
{
    template <typename API>
    class MockResetter : public cenpy::graphic::shader::component::program::IProgramResetter<API>
    {
    public:
        MOCK_METHOD(void, resetProgram, (std::shared_ptr<typename API::ProgramContext> context), (override));
    };
}
