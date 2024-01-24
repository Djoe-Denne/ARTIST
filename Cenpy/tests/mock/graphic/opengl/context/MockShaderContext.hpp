// ShaderContext.hpp

#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/pipeline/component/shader/MockLoader.hpp>
#include <graphic/opengl/pipeline/component/shader/MockFreer.hpp>
#include <graphic/opengl/pipeline/component/shader/MockReader.hpp>

namespace cenpy::mock::graphic::opengl::context
{
    
    class MockShaderContext : public cenpy::graphic::context::ShaderContext<graphic::api::MockOpenGL>
    {
    public:
        template <auto PROFILE>
        using Loader = opengl::pipeline::component::shader::MockLoader< PROFILE>;
        template <auto PROFILE>
        using Freer = opengl::pipeline::component::shader::MockFreer< PROFILE>;
        template <auto PROFILE>
        using Reader = opengl::pipeline::component::shader::MockReader< PROFILE>;

        MOCK_METHOD(void, setShaderID, (GLuint shaderID), ());
        MOCK_METHOD(GLuint, getShaderID, (), (const));
        MOCK_METHOD(GLenum, getGLShaderType, (), (const));
        MOCK_METHOD(void, setShaderType, (cenpy::graphic::context::ShaderType shaderType), (override));
        MOCK_METHOD(cenpy::graphic::context::ShaderType, getShaderType, (), (const, override));
        MOCK_METHOD(void, setShaderPath, (const std::string &shaderPath), (override));
        MOCK_METHOD(const std::string &, getShaderPath, (), (const, override));
        MOCK_METHOD(void, setShaderCode, (const std::string &shaderCode), (override));
        MOCK_METHOD(const std::string &, getShaderCode, (), (const, override));
    };
}
