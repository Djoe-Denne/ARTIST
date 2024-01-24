// file: Reader.hpp

#pragma once

#include <string>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <fstream>
#include <sstream>
#include <format>
#include <common/exception/TraceableException.hpp>
#include <graphic/opengl/profile/Shader.hpp>

namespace cenpy::graphic::opengl::pipeline::component::shader
{
    template <auto PROFILE>
    class OpenGLShaderReader
    {
    };

    template <>
    class OpenGLShaderReader<graphic::opengl::profile::Shader::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::ShaderContext> context)
        {
            context->setShaderCode("");
            std::ifstream shaderFile;

            // ensure ifstream objects can throw exceptions
            shaderFile.exceptions(std::ifstream::badbit);

            try
            {
                shaderFile.open(context->getShaderPath());
                std::stringstream shaderStream;

                shaderStream << shaderFile.rdbuf(); // read file's buffer contents into streams
                shaderFile.close();

                context->setShaderCode(shaderStream.str());
            }
            catch (std::ifstream::failure &e)
            {
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n{}", e.what()));
            }
        }
    };
}
