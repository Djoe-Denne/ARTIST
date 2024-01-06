// ProgramContext.hpp

#pragma once

#include <graphic/MockApi.hpp>
#include <graphic/context/ProgramContext.hpp>
#include <graphic/shader/component/program/MockUser.hpp>
#include <graphic/shader/component/program/MockResetter.hpp>

namespace cenpy::mock::graphic
{
    namespace opengl::context
    {
        class MockProgramContext : public cenpy::graphic::context::ProgramContext<graphic::api::MockOpenGL>
        {
        public:
            using User = shader::opengl::component::program::MockUser;
            using Resetter = shader::opengl::component::program::MockResetter;
        };
    }
}