#pragma once

#include <memory>
#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/pipeline/component/shader/Freer.hpp>

namespace cenpy::mock::graphic::pipeline::opengl::component::shader
{
    template <typename API>
    class MockFreer : public cenpy::graphic::pipeline::component::shader::IShaderFreer<API>
    {
    public:
        MOCK_METHOD(void, freeShader, (std::shared_ptr<typename API::ShaderContext> context), (override));
    };
}