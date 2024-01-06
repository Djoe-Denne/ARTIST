#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/pass/User.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    class MockUser : public cenpy::graphic::shader::component::pass::IPassUser<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, usePass, (std::shared_ptr<typename graphic::api::MockOpenGL::PassContext>), (override));
    };
}
