// file: Loader.hpp

#pragma once

#include <string>
#include <format>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/ShaderContext.hpp>

namespace cenpy::graphic::shader
{
    namespace component::shader
    {
        /**
         * @interface IShaderLoader
         * @brief Interface for shader loading operations.
         *
         * IShaderLoader defines an interface for loading shaders. It abstracts the
         * mechanism of how shaders are loaded, allowing for different implementations
         * for various graphics APIs.
         */
        template <typename API>
        class IShaderLoader
        {
        public:
            virtual ~IShaderLoader() = default;

            /**
             * @brief Load the shader with the given code and context.
             * @param shaderCode The shader source code.
             * @param context ShaderContext providing API-specific details and state management.
             */
            virtual void loadShader(std::shared_ptr<typename API::ShaderContext> context) = 0;
        };

    }

    namespace opengl::component::shader
    {
        /**
         * @class OpenGLShaderLoader
         * @brief OpenGL implementation of IShaderLoader.
         *
         * OpenGLShaderLoader is responsible for loading shaders in an OpenGL context.
         * It compiles the shader source code and manages shader objects in OpenGL.
         */
        class OpenGLShaderLoader : public graphic::shader::component::shader::IShaderLoader<graphic::api::OpenGL>
        {
        public:
            void loadShader(std::shared_ptr<typename graphic::api::OpenGL::ShaderContext> openglContext) override
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
            bool checkCompileErrors(GLuint shaderID) const
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
}
