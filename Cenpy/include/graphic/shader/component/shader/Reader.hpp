// file: Reader.hpp

#pragma once

#include <string>
#include <graphic/Api.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <fstream>
#include <sstream>
#include <format>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic::shader::component::shader
{
    template <typename API>
    class IShaderReader
    {
    public:
        virtual ~IShaderReader() = default;

        virtual void readShader(std::shared_ptr<typename API::ShaderContext> context)
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

namespace cenpy::graphic::shader::opengl::component::shader
{
    class OpenGLShaderReader : public graphic::shader::component::shader::IShaderReader<graphic::api::OpenGL>
    {
    };
}
