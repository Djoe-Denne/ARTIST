// ShaderContext.hpp

#pragma once
#include <GL/glew.h>
#include <graphic/Api.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic
{

    namespace shader::opengl::component::shader
    {
        class OpenGLShaderLoader;
        class OpenGLShaderFreer;
        class OpenGLShaderReader;
    }
    namespace context
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
         * @class ShaderContext
         * @brief Abstract base class for shader context.
         *
         * The ShaderContext class provides an interface for managing shader-specific
         * details and state. It serves as a base for API-specific implementations
         * to handle shader resources and state management in a way that is tailored
         * to each graphics API.
         */
        template <typename API>
        class ShaderContext
        {
        public:
            virtual ~ShaderContext() = default;

            virtual void setShaderType(ShaderType shaderType)
            {
                m_shaderType = shaderType;
            }

            [[nodiscard]] virtual graphic::context::ShaderType getShaderType() const
            {
                return m_shaderType;
            }

            virtual void setShaderPath(const std::string &shaderPath)
            {
                m_shaderPath = shaderPath;
            }

            [[nodiscard]] virtual const std::string &getShaderPath() const
            {
                return m_shaderPath;
            }

            virtual void setShaderCode(const std::string &shaderCode)
            {
                m_shaderCode = shaderCode;
            }

            [[nodiscard]] virtual const std::string &getShaderCode() const
            {
                return m_shaderCode;
            }

        private:
            ShaderType m_shaderType;  ///< Shader type
            std::string m_shaderPath; // Path to the shader source code
            std::string m_shaderCode; // The code of the shader
        };
    }

    namespace opengl::context
    {
        /**
         * @class OpenGLShaderContext
         * @brief OpenGL-specific implementation of ShaderContext.
         *
         * OpenGLShaderContext manages OpenGL-specific details and state for shaders.
         * It provides mechanisms to store and retrieve OpenGL-specific data, such as
         * shader IDs, necessary for shader operations in an OpenGL context.
         */
        class OpenGLShaderContext : public graphic::context::ShaderContext<graphic::api::OpenGL>
        {
        public:
            using Loader = shader::opengl::component::shader::OpenGLShaderLoader;
            using Freer = shader::opengl::component::shader::OpenGLShaderFreer;
            using Reader = shader::opengl::component::shader::OpenGLShaderReader;
            OpenGLShaderContext() {}

            void setShaderID(GLuint shaderID)
            {
                m_shaderID = shaderID;
            }

            GLuint getShaderID() const
            {
                return m_shaderID;
            }

            /**
             * @brief Converts the ShaderType enum to the corresponding OpenGL shader type.
             *
             * @return The OpenGL shader type.
             * @throws TraceableException if the shader type is unknown.
             */
            GLenum getGLShaderType() const
            {
                switch (getShaderType())
                {
                    using enum graphic::context::ShaderType;
                case VERTEX:
                    return GL_VERTEX_SHADER;
                case FRAGMENT:
                    return GL_FRAGMENT_SHADER;
                case GEOMETRY:
                    return GL_GEOMETRY_SHADER;
                case TESS_CONTROL:
                    return GL_TESS_CONTROL_SHADER;
                case TESS_EVALUATION:
                    return GL_TESS_EVALUATION_SHADER;
                case COMPUTE:
                    return GL_COMPUTE_SHADER;
                default:
                    throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::UNKNOWN_SHADER_TYPE");
                }
            }

        private:
            GLuint m_shaderID; ///< OpenGL shader ID
        };
    }
}