// file: Loader.hpp

#pragma once

#include <string>
#include <format>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/profile/Shader.hpp>

namespace cenpy::graphic::opengl::pipeline::component::shader
{
    /**
     * @class OpenGLShaderLoader
     * @brief OpenGL implementation of IShaderLoader.
     *
     * OpenGLShaderLoader is responsible for loading shaders in an OpenGL context.
     * It compiles the shader source code and manages shader objects in OpenGL.
     */
    template <auto PROFILE>
    class OpenGLShaderLoader
    {
    };

    template <>
    class OpenGLShaderLoader<graphic::opengl::profile::Shader::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::ShaderContext> openglContext)
        {
            // Create a shader object
            GLuint shaderID = glCreateShader(openglContext->getGLShaderType());
            const char *shaderCodeCStr = openglContext->getShaderCode().c_str();
            glShaderSource(shaderID, 1, &shaderCodeCStr, nullptr);
            glCompileShader(shaderID);

            // Check for shader compile errors
            if (!checkCompileErrors(shaderID))
            {
                glDeleteShader(shaderID); // Don't leak the shader.
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::COMPILATION_FAILED\n"));
            }

            // Store the shader ID in the OpenGL context
            openglContext->setShaderID(shaderID);
        }

    private:
        static bool checkCompileErrors(GLuint shaderID)
        {
            GLint success;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                GLchar infoLog[512];
                glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
                std::cerr << "Shader compilation error: " << infoLog << std::endl;
                return false;
            }
            return true;
        }
    };
}
