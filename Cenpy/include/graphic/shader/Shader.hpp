/**
 * @file Shader.hpp
 * @brief Defines the shader interface and OpenGL implementation for shader objects.
 *
 * This file contains the abstract definition of a shader object and its OpenGL-specific implementation.
 * The shader system is designed to be adaptable for multiple graphics APIs, including Vulkan, DirectX, and Metal.
 * The current implementation under the 'cenpy::graphic::shader::opengl' namespace is tailored for OpenGL.
 *
 * @author Djoé DENNE
 * @date 13/12/2023
 */

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
     * @class BaseShader
     * @brief Interface for a Shader object, providing basic functionalities common across various graphics APIs.
     *
     * BaseShader is an abstract class that defines the core functionalities for shader objects,
     * such as loading shader code, managing shader types, and handling shader-specific operations.
     * This class is intended to be subclassed for specific graphics API implementations like OpenGL, Vulkan, and DirectX.
     */
    class BaseShader
    {
    public:
        /**
         * @brief Destructor for BaseShader.
         */
        virtual ~BaseShader() = default;

        /**
         * @brief Get the path of the shader file.
         * @return The path of the shader file.
         */
        [[nodiscard]] const std::string &getShaderPath() const
        {
            return m_shaderPath;
        }

        /**
         * @brief Get the type of the shader.
         * @return The type of the shader.
         */
        [[nodiscard]] const ShaderType &getShaderType() const
        {
            return m_shaderType;
        }

        /**
         * @brief Get the code of the shader.
         * @return The code of the shader.
         */
        [[nodiscard]] const std::string &getShaderCode() const
        {
            return m_shaderCode;
        }

    protected:
        /**
         * @brief Constructor for BaseShader.
         * @param shaderPath The path of the shader file.
         * @param shaderType The type of the shader.
         */
        BaseShader(const std::string &shaderPath, const ShaderType &shaderType) : m_shaderPath(shaderPath), m_shaderType(shaderType)
        {
        }

        /**
         * @brief Read the shader code from the file.
         * @return The code of the shader.
         * @throws common::exception::TraceableException<std::runtime_error> If the shader file cannot be read.
         */
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

        /**
         * @brief Free the resources used by the shader.
         */
        virtual void free() = 0;

        /**
         * @brief Load the shader.
         */
        virtual void load() = 0;

    private:
        std::string m_shaderPath; ///< The path of the shader file.
        ShaderType m_shaderType;  ///< The type of the shader.
        std::string m_shaderCode; ///< The code of the shader.
    };

    namespace opengl
    {
        /**
         * @brief Represents a shader object.
         *
         * The Shader class is responsible for loading, compiling, and managing a shader object in OpenGL.
         * It inherits from the BaseShader class and provides additional functionality specific to shaders.
         */
        class Shader : public BaseShader
        {
        public:
            /**
             * @brief Constructs a Shader object.
             *
             * @param shaderPath The path to the shader source code file.
             * @param shaderType The type of the shader.
             */
            Shader(const std::string &shaderPath, const ShaderType &shaderType) : BaseShader(shaderPath, shaderType)
            {
            }

            /**
             * @brief Loads and compiles the shader.
             *
             * This function reads the shader source code from the file, compiles it, and checks for any compile errors.
             * If the shader source code cannot be read or the shader cannot be compiled, an exception is thrown.
             */
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

            /**
             * @brief Frees the shader object.
             *
             * This function deletes the shader object from the GPU memory.
             */
            void free() override
            {
                glDeleteShader(m_location);
            }

            /**
             * @brief Gets the location of the shader object.
             *
             * @return The location of the shader object.
             */
            [[nodiscard]] virtual GLuint getLocation() const
            {
                return m_location;
            }

        protected:
            /**
             * @brief Converts the ShaderType enum to the corresponding OpenGL shader type.
             *
             * @param shaderType The type of the shader.
             * @return The OpenGL shader type.
             * @throws TraceableException if the shader type is unknown.
             */
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
             * This function checks for compile errors in a shader and throws an exception if any errors are found.
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
             *
             * This function checks for compile errors in a shader and throws an exception if any errors are found.
             *
             * @param shader The shader to check for errors.
             * @param errorMessage The error message to include in the exception.
             * @throws TraceableException if the shader cannot be compiled.
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

        private:
            GLuint m_location;
        };
        /** END Utility functions */
    } // namespace opengl
} // namespace cenpy::graphic::shader