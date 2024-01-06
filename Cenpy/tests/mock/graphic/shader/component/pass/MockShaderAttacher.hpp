#pragma once

#include <memory>
#include <graphic/MockApi.hpp>
#include <gmock/gmock.h>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::pass
{
    class MockShaderAttacher : public cenpy::graphic::shader::component::pass::IShaderAttacher<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, attachShaders, (std::shared_ptr<typename graphic::api::MockOpenGL::PassContext> openglContext), (override));
    };
}
