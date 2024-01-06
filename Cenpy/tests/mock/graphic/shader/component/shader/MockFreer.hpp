#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/shader/Freer.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::shader
{
    class MockFreer : public cenpy::graphic::shader::component::shader::IShaderFreer<graphic::api::MockOpenGL>
    {
    public:
        MOCK_METHOD(void, freeShader, (std::shared_ptr<typename graphic::api::MockOpenGL::ShaderContext> context), (override));
    };
}