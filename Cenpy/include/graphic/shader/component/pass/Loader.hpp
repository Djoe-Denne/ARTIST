#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>

namespace cenpy::graphic::shader
{
    namespace component::pass
    {
        /**
         * @interface ILoader
         * @brief Interface for loading shader passes.
         */
        template <typename API>
        class ILoader
        {
        public:
            virtual ~ILoader() = default;

            /**
             * @brief Load resources and state for a shader pass.
             * @param context PassContext for managing pass-specific details.
             */
            virtual void loadPass(std::shared_ptr<typename API::PassContext> context) = 0;
        };
    }

    namespace opengl::component::pass
    {
        class OpenGLLoader : public graphic::shader::component::pass::ILoader<graphic::api::OpenGL>
        {
        public:
            OpenGLLoader() = default;
            explicit OpenGLLoader(const std::shared_ptr<graphic::shader::component::pass::IShaderAttacher<graphic::api::OpenGL>> attacher) : m_attacher(attacher) {}

            void setAttacher(const std::shared_ptr<graphic::shader::component::pass::IShaderAttacher<graphic::api::OpenGL>> attacher) { m_attacher = attacher; }

            void loadPass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override
            {
                if (!openglContext)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM::NON_OPENGL_CONTEXT"));
                }

                GLuint programId = glCreateProgram();
                if (programId == 0)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM_CREATION_FAILED\nFailed to create shader program."));
                }

                // Save the created program ID in the context
                openglContext->setProgramId(programId);
                m_attacher->attachShaders(openglContext);

                // Link the program
                glLinkProgram(programId);

                if (!checkLinkErrors(programId))
                {
                    glDeleteProgram(programId);
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM::LINK_FAILED"));
                }
            }

            /**
             * @brief Checks for link errors in an OpenGL program.
             * @param programId The ID of the OpenGL program to check.
             * @return True if no linking errors are found, false otherwise.
             */
            bool checkLinkErrors(GLuint programId) const
            {
                GLint isLinked = 0;
                glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
                if (isLinked == GL_FALSE)
                {
                    GLint maxLength = 0;
                    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

                    std::vector<GLchar> infoLog(maxLength);
                    glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

                    std::cerr << "Program link error: " << infoLog.data() << std::endl;
                    return false;
                }
                return true;
            }

        private:
            std::shared_ptr<graphic::shader::component::pass::IShaderAttacher<graphic::api::OpenGL>> m_attacher;
        };
    }

}