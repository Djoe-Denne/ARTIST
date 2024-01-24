// ShaderContext.hpp

#pragma once
#include <GL/glew.h>
#include <graphic/Api.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic
{

    namespace opengl::pipeline::component::shader
    {
        template <auto PROFILE>
        class OpenGLShaderLoader;
        template <auto PROFILE>
        class OpenGLShaderFreer;
        template <auto PROFILE>
        class OpenGLShaderReader;
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
            template <auto PROFILE>
            using Loader = opengl::pipeline::component::shader::OpenGLShaderLoader<PROFILE>;
            template <auto PROFILE>
            using Freer = opengl::pipeline::component::shader::OpenGLShaderFreer<PROFILE>;
            template <auto PROFILE>
            using Reader = opengl::pipeline::component::shader::OpenGLShaderReader<PROFILE>;

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