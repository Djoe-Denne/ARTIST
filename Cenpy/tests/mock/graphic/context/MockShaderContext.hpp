// ShaderContext.hpp

#pragma once

#include <gmock/gmock.h>
#include <graphic/MockApi.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/shader/MockLoader.hpp>
#include <graphic/shader/component/shader/MockFreer.hpp>
#include <graphic/shader/component/shader/MockReader.hpp>

namespace cenpy::mock::graphic
{

    namespace opengl::context
    {
        template <typename API>
        class MockShaderContext : public cenpy::graphic::context::ShaderContext<API>
        {
        public:
            using Loader = shader::opengl::component::shader::MockLoader<API>;
            using Freer = shader::opengl::component::shader::MockFreer<API>;
            using Reader = shader::opengl::component::shader::MockReader<API>;

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
}