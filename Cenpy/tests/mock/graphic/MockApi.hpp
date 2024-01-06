// Api.hpp

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace cenpy::mock::graphic
{
    namespace opengl::context
    {
        class MockShaderContext;
        class MockPassContext;
        class MockUniformContext;
        class MockProgramContext;
    }
    namespace api
    {
        /**
         * @class OpenGL
         * @brief Encapsulation of the OpenGL context configuration for shader management.
         *
         * The OpenGL class acts as a part of the configuration layer for the shader management system,
         * specifically tailored for the OpenGL graphics API. It defines the type of ShaderContext to
         * be used when working with OpenGL shaders. This class is utilized as a template parameter
         * in the Shader class to provide the necessary OpenGL-specific context, loaders, and freers.
         *
         * Usage:
         *   Shader<OpenGL> shader("path/to/shader", ShaderType::VERTEX);
         *
         * This approach allows for clear and concise configuration, making the shader system adaptable
         * to different graphics APIs by simply changing the template argument.
         */
        class MockOpenGL
        {
        public:
            using ShaderContext = graphic::opengl::context::MockShaderContext;
            using PassContext = graphic::opengl::context::MockPassContext;
            using UniformContext = graphic::opengl::context::MockUniformContext;
            using ProgramContext = graphic::opengl::context::MockProgramContext;
        };
    }
}