#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/shader/component/pass/Freer.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    namespace shader = cenpy::graphic::shader;
    // Mock class for OpenGLPassFreer
    class MockFreer : public cenpy::graphic::shader::component::pass::IPassFreer<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, freePass, (std::shared_ptr<typename graphic::api::MockOpenGL::PassContext>), (override));
    };

}