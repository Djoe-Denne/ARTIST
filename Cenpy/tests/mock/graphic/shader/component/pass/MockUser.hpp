#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/pass/User.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    template <typename API>
    class MockUser : public cenpy::graphic::shader::component::pass::IPassUser<API>
    {
    public:
        MOCK_METHOD(void, usePass, (std::shared_ptr<typename API::PassContext>), (override));
    };
}
