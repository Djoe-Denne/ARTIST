#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/pipeline/MockUniform.hpp>
#include <graphic/opengl/context/MockShaderContext.hpp>
#include <graphic/pipeline/Shader.hpp>

namespace cenpy::mock::graphic::pipeline
{
    namespace api = cenpy::mock::graphic::api;
    namespace context = cenpy::graphic::context;
    namespace pipeline = cenpy::graphic::pipeline;

    template <typename API>
    class MockShader : public pipeline::IShader<API>
    {
    public:
        MockShader() : pipeline::IShader<API>("", context::ShaderType::VERTEX) {}
        MockShader(const std::string &path, context::ShaderType type) : pipeline::IShader<API>(path, type) {}

        MOCK_METHOD(void, free, (), (override));
        MOCK_METHOD(void, load, (), (override));
        MOCK_METHOD(const std::shared_ptr<typename API::ShaderContext> &, getContext, (), (const, override));

    protected:
        MOCK_METHOD(void, load, (std::shared_ptr<typename API::ShaderContext>), (override));
        MOCK_METHOD(void, free, (std::shared_ptr<typename API::ShaderContext>), (override));
        MOCK_METHOD(void, read, (std::shared_ptr<typename API::ShaderContext>), (override));
    };

}
