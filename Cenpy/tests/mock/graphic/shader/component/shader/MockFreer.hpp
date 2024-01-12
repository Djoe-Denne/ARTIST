#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/shader/Freer.hpp>

namespace cenpy::mock::graphic::shader::opengl::component::shader
{
    template <typename API>
    class MockFreer : public cenpy::graphic::shader::component::shader::IShaderFreer<API>
    {
    public:
        MOCK_METHOD(void, freeShader, (std::shared_ptr<typename API::ShaderContext> context), (override));
    };
}