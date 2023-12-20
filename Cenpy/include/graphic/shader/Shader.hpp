#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <format>
#include <fstream>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic::shader
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESS_CONTROL,
        TESS_EVALUATION,
        COMPUTE
    };

    /**
     * @brief Interface for a Shader object.
     */
    class BaseShader
    {
    public:
        virtual ~BaseShader() = default;

        [[nodiscard]] const std::string &getShaderPath() const
        {
            return m_shaderPath;
        }

        [[nodiscard]] const ShaderType &getShaderType() const
        {
            return m_shaderType;
        }

        [[nodiscard]] const std::string &getShaderCode() const
        {
            return m_shaderCode;
        }

    protected:
        BaseShader(const std::string &shaderPath, const ShaderType &shaderType) : m_shaderPath(shaderPath), m_shaderType(shaderType)
        {
        }

        [[nodiscard]] const std::string &readShader()
        {
            m_shaderCode.clear();
            std::ifstream shaderFile;

            // ensure ifstream objects can throw exceptions
            shaderFile.exceptions(std::ifstream::badbit);

            try
            {
                shaderFile.open(m_shaderPath);
                std::stringstream shaderStream;

                shaderStream << shaderFile.rdbuf(); // read file's buffer contents into streams
                shaderFile.close();

                m_shaderCode = shaderStream.str();
            }
            catch (std::ifstream::failure &e)
            {
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n{}", e.what()));
            }
            return m_shaderCode;
        }

        virtual void free() = 0;
        virtual void load() = 0;

    private:
        std::string m_shaderPath;
        ShaderType m_shaderType;
        std::string m_shaderCode;
    };

    namespace opengl
    {
        class Shader : public BaseShader
        {
        public:
            Shader(const std::string &shaderPath, const ShaderType &shaderType) : BaseShader(shaderPath, shaderType)
            {
            }

            void load() override
            {
                GLenum glShaderType = getGLShaderType(getShaderType());
                std::string shaderCode = readShader();
                if (shaderCode.empty())
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n{}", getShaderPath()));
                }
                const char *shaderCodeCStr = shaderCode.c_str();

                m_location = glCreateShader(glShaderType);
                glShaderSource(m_location, 1, &shaderCodeCStr, nullptr);
                glCompileShader(m_location);

                checkCompileErrors(m_location);
            }

            void free() override
            {
                glDeleteShader(m_location);
            }

            [[nodiscard]] const GLuint &getLocation() const
            {
                return m_location;
            }

        protected:
            GLenum getGLShaderType(const ShaderType &shaderType)
            {
                switch (shaderType)
                {
                case ShaderType::VERTEX:
                    return GL_VERTEX_SHADER;
                case ShaderType::FRAGMENT:
                    return GL_FRAGMENT_SHADER;
                case ShaderType::GEOMETRY:
                    return GL_GEOMETRY_SHADER;
                case ShaderType::TESS_CONTROL:
                    return GL_TESS_CONTROL_SHADER;
                case ShaderType::TESS_EVALUATION:
                    return GL_TESS_EVALUATION_SHADER;
                case ShaderType::COMPUTE:
                    return GL_COMPUTE_SHADER;
                default:
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::UNKNOWN_SHADER_TYPE"));
                }
            }

            /**
             * @brief Checks for compile errors in a shader.
             *
             * This function checks for compile errors in a shader and prints an error message if any errors are found.
             *
             * @param shader The shader to check for errors.
             * @throws TraceableException if the shader cannot be compiled.
             */
            void checkCompileErrors(GLuint shader) const
            {
                checkCompileErrors(shader, "SHADER");
            }

            /**
             * @brief Checks for compile errors in a shader.
             * @throw TraceableException if the shader cannot be compiled.
             */
            void checkCompileErrors(GLuint shader, const std::string &errorMessage) const
            {
                GLint success;
                GLchar infoLog[512];
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

                if (!success)
                {
                    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::{}::COMPILATION_FAILED\n{}", errorMessage, infoLog));
                }
            }
            /** END Utility functions */

        private:
            GLuint m_location;
        };
    } // namespace opengl
} // namespace cenpy::graphic::shader