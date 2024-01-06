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
        class MockShaderContext : public cenpy::graphic::context::ShaderContext<graphic::api::MockOpenGL>
        {
        public:
            using Loader = shader::opengl::component::shader::MockLoader;
            using Freer = shader::opengl::component::shader::MockFreer;
            using Reader = shader::opengl::component::shader::MockReader;

            MOCK_METHOD(void, setShaderID, (GLuint shaderID), ());
            MOCK_METHOD(GLuint, getShaderID, (), (const));
            MOCK_METHOD(GLenum, getGLShaderType, (), (const));
        };
    }
}