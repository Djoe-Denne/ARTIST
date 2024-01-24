// file: Freer.hpp

#pragma once

#include <string>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/profile/Shader.hpp>

namespace cenpy::graphic::opengl::pipeline::component::shader
{
    /**
     * @class OpenGLShaderFreer
     * @brief OpenGL implementation of IShaderFreer.
     *
     * OpenGLShaderFreer is responsible for freeing or deleting shaders in an OpenGL context.
     * It ensures that OpenGL shader objects are properly deleted and resources are released.
     */
    template <auto PROFILE>
    class OpenGLShaderFreer
    {
    };

    template <>
    class OpenGLShaderFreer<graphic::opengl::profile::Shader::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::ShaderContext> openglContext)
        {
            GLuint shaderID = openglContext->getShaderID();

            if (shaderID != 0)
            {
                glDeleteShader(shaderID);
                openglContext->setShaderID(0); // Reset the shader ID in the context
            }
        }
    };
}
