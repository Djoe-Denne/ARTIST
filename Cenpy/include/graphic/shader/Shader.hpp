#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <format>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <utils.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/shader/Uniform.hpp>

namespace cenpy::graphic::shader
{
    /**
     * @brief A class representing a multipass shader.
     *
     * This class provides functionality to create and manage multipass shaders.
     * It supports loading shader source code from file paths.
     *
     * Example usage:
     * @code
     * Shader shader("vertex.glsl", "fragment.glsl");
     * @endcode
     */
    class Shader
    {
    public:
        /**
         * @brief Constructs a Shader object with the specified vertex and fragment shader paths.
         *
         * @tparam T The type of the shader paths. It can be either const char* or std::string.
         * @param vertexPath The path to the vertex shader source code.
         * @param fragmentPath The path to the fragment shader source code.
         */
        template <typename T>
            requires std::is_same_v<T, const char *> || std::is_same_v<T, std::string>
        Shader(const char *vertexPath, const T &fragmentPath) : m_program(1)
        {
            createPragram(vertexPath, fragmentPath);
            readUniforms();
        }

        /**
         * @brief Constructs a Shader object with the specified vertex and fragment shader paths, and additional shader paths.
         *
         * @tparam T The type of the shader paths. It can be either const char* or std::string.
         * @tparam Args The types of the additional shader paths.
         * @param vertexPath The path to the vertex shader source code.
         * @param fragmentPath The path to the fragment shader source code.
         * @param args Additional fragement shader paths.
         */
        template <typename T, typename... Args>
            requires std::is_same_v<T, const char *> || std::is_same_v<T, std::string>
        Shader(const T &vertexPath, const T &fragmentPath, Args &&...args) : m_program(sizeof...(args) + 1)
        {
            createPragram(vertexPath, fragmentPath, std::forward<Args>(args)...);
            readUniforms();
        }

        /**
         * @brief Prepares the shader for use. Just a nice way to start the fluent interface.
         */
        Shader &prepare()
        {
            return *this;
        }

        /**
         * @brief Sets a uniform value.
         *
         * @tparam T The type of the uniform value.
         * @param name The name of the uniform.
         * @param value The value of the uniform.
         * @param number The number of elements in the uniform.
         * @return A reference to the shader.
         * @throws TraceableException if the uniform is not found.
         */
        template <typename T>
        Shader &withUniform(const std::string &name, const T &value, const int &number = 1)
        {
            if (m_uniforms[m_program[m_currentProgram]].contains(name))
            {
                m_uniforms[m_program[m_currentProgram]][name].set(value, number);
            }
            else
            {
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::UNIFORM_NOT_FOUND\nUniform {} not found", name));
            }
            return *this;
        }

        /**
         * @brief Checks if there is a next element.
         *
         * @return true if there is a next element, false otherwise.
         */
        bool
        hasNext() const
        {
            return m_currentProgram < m_program.size() - 1;
        }

        /**
         * @brief Sets the next shader to be used.
         *
         * @details If there is no next shader, resets the current shader to the first one and unset the current shader.
         *
         * @return true if the next shader was set successfully, false otherwise.
         */
        bool useNext()
        {
            if (hasNext())
            {
                m_currentProgram++;
                glUseProgram(m_program[m_currentProgram]);
            }
            else
            {
                reset();
            }
            return hasNext();
        }

        /**
         * @brief Resets the shader to its initial state. unset shader in OpenGL context.
         */
        void reset()
        {
            m_currentProgram = 0;
            glUseProgram(0);
        }

        /**
         * @brief Gets the current shader program.
         *
         * @return The current shader program.
         */
        GLuint getProgram() const
        {
            return m_program[m_currentProgram];
        }

    protected:
        template <typename T, typename... Args>
            requires std::is_same_v<T, const char *> || std::is_same_v<T, std::string>
        void createPragram(const T &vertexPath, const T &fragmentPath, Args &&...args)
        {
            GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
            createPragram(vertexShader, fragmentPath, std::forward<Args>(args)...);
            glDeleteShader(vertexShader);
        }

        /**
         * @brief Reads the uniforms from the shader program.
         *
         * This function reads the uniforms from the shader program and stores them in a map.
         * The map is indexed by the uniform name and contains the uniform location, type, and size.
         */
        void readUniforms()
        {
            for (auto &program : m_program)
            {
                GLint count;
                // get number of uniforms
                glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

                auto uniforms = std::unordered_map<std::string, opengl::Uniform, collection_utils::StringHash, collection_utils::StringEqual>(count);

                for (int i = 0; i < count; i++)
                {
                    char name[256];
                    GLsizei length;
                    GLint size;
                    GLenum type;

                    // get uniform information
                    glGetActiveUniform(program, i, sizeof(name), &length, &size, &type, name);
                    name[length] = '\0';
                    // add uniform on time only, meaning different fragment shader o a multipass shader can have the same uniform, but it must be the exact same type and size
                    if (uniforms.contains(name))
                    {
                        GLuint location = glGetUniformLocation(program, name);
                        uniforms[name] = opengl::Uniform(location, type, size);
                    }
                    else
                    {
                        throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::UNIFORM_DEFINE_TWICE\nUniform {} defined twice", name));
                    }
                }
            }
        }

        /**
         * @brief Creates a shader program with a vertex shader and multiple fragment shaders.
         *
         * This function is a variadic template that allows the creation of a shader program with a vertex shader and multiple fragment shaders.
         * The vertex shader is provided as a GLuint, while the fragment shaders can be provided as const char* or std::string.
         *
         * @tparam T The type of the fragment shader path. Can be const char* or std::string.
         * @tparam Args The types of additional fragment shader paths.
         * @param vertexShader The vertex shader as a GLuint.
         * @param fragmentPath The path to the first fragment shader.
         * @param args Additional fragment shader paths.
         */
        template <typename T, typename... Args>
            requires std::is_same_v<T, const char *> || std::is_same_v<T, std::string>
        void createPragram(const GLuint &vertexShader, const T &fragmentPath, Args &&...args)
        {
            createPragram(vertexShader, fragmentPath);
            createPragram(vertexShader, std::forward<Args>(args)...);
        }

        /**
         * @brief Creates a shader program with a vertex shader and a fragment shader.
         *
         * This function creates a shader program with a vertex shader and a fragment shader.
         * The paths to the vertex and fragment shaders are provided as std::string.
         *
         * @param vertexPath The path to the vertex shader.
         * @param fragmentPath The path to the fragment shader.
         */
        void createPragram(const std::string &vertexPath, const std::string &fragmentPath)
        {
            createPragram(vertexPath.c_str(), fragmentPath.c_str());
        }

        /**
         * @brief Creates a shader program with a vertex shader and a fragment shader.
         *
         * This function creates a shader program with a vertex shader and a fragment shader.
         * The paths to the vertex and fragment shaders are provided as const char*.
         *
         * @param vertexPath The path to the vertex shader.
         * @param fragmentPath The path to the fragment shader.
         */
        void createPragram(const char *vertexPath, const char *fragmentPath)
        {
            GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
            createPragram(vertexShader, fragmentPath);
            glDeleteShader(vertexShader);
        }

        /**
         * @brief Creates a shader program with a vertex shader and a fragment shader.
         *
         * This function creates a shader program with a vertex shader and a fragment shader.
         * The vertex shader is provided as a GLuint, while the fragment shader path is provided as const char*.
         *
         * @param vertexShader The vertex shader as a GLuint.
         * @param fragmentPath The path to the fragment shader.
         */
        void createPragram(const GLuint &vertexShader, const char *fragmentPath)
        {
            GLuint fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

            GLuint program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            checkCompileErrors(program, "PROGRAM");

            glDeleteShader(fragmentShader);

            m_program.emplace_back(program);
        }

        /**
         * @brief Loads a shader from a file and compiles it.
         *
         * This function loads a shader from a file, compiles it, and returns the shader as a GLuint.
         *
         * @param shaderPath The path to the shader file.
         * @param shaderType The type of the shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
         * @return The compiled shader as a GLuint.
         * @throws TraceableException if the shader file cannot be read or the shader cannot be compiled.
         */
        GLuint loadShader(const char *shaderPath, GLenum shaderType)
        {
            std::string shaderCode;
            std::ifstream shaderFile;

            // ensure ifstream objects can throw exceptions
            shaderFile.exceptions(std::ifstream::badbit);

            try
            {
                shaderFile.open(shaderPath);
                std::stringstream shaderStream;

                shaderStream << shaderFile.rdbuf();
                shaderFile.close();

                shaderCode = shaderStream.str();
            }
            catch (std::ifstream::failure &e)
            {
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n{}", e.what()));
            }

            m_shaderPaths.push_back(shaderPath);

            const char *shaderCodeCStr = shaderCode.c_str();
            GLuint shader;

            shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &shaderCodeCStr, nullptr);
            glCompileShader(shader);

            checkCompileErrors(shader);
            return shader;
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
        std::vector<GLuint> m_program;
        std::unordered_map<GLuint, std::unordered_map<std::string, opengl::Uniform, collection_utils::StringHash, collection_utils::StringEqual>> m_uniforms;
        u_int16_t m_currentProgram = 0;
        std::vector<std::string> m_shaderPaths;
    };
} // namespace cenpy::graphic::shader