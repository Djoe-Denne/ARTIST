#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/MockShaderContext.hpp>
#include <graphic/pipeline/Shader.hpp>

namespace cenpy::mock::graphic::pipeline
{
    namespace api = cenpy::mock::graphic::api;
    namespace context = cenpy::graphic::context;
    namespace pipeline = cenpy::graphic::pipeline;

    template <typename API>
    class MockShader : public pipeline::Shader<API>
    {
    public:
        MockShader()
            : pipeline::Shader<API>("", context::ShaderType::VERTEX)
        {
        }
        MockShader(const std::string &shaderPath, const context::ShaderType &shaderType)
            : pipeline::Shader<API>(shaderPath, shaderType)
        {
        }

        MOCK_METHOD(void, free, (), (override));
        MOCK_METHOD(void, load, (), (override));
        MOCK_METHOD(const std::shared_ptr<typename API::ShaderContext> &, getContext, (), (const, override));
    };

}
