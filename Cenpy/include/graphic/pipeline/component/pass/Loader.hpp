#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/pipeline/component/pass/ShaderAttacher.hpp>

namespace cenpy::graphic::pipeline
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
        class OpenGLLoader : public graphic::pipeline::component::pass::ILoader<graphic::api::OpenGL>
        {
        public:
            OpenGLLoader() = default;
            explicit OpenGLLoader(const std::shared_ptr<graphic::pipeline::component::pass::IShaderAttacher<graphic::api::OpenGL>> attacher) : m_attacher(attacher) {}

            void setAttacher(const std::shared_ptr<graphic::pipeline::component::pass::IShaderAttacher<graphic::api::OpenGL>> attacher) { m_attacher = attacher; }

            void loadPass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext) override
            {
                if (!openglContext)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM::NON_OPENGL_CONTEXT"));
                }

                GLuint passID = glCreateProgram();
                if (passID == 0)
                {
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM_CREATION_FAILED\nFailed to create shader pipeline."));
                }

                // Save the created pipeline ID in the context
                openglContext->setPassID(passID);
                m_attacher->attachShaders(openglContext);

                // Link the pipeline
                glLinkProgram(passID);

                if (!checkLinkErrors(passID))
                {
                    glDeleteProgram(passID);
                    throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM::LINK_FAILED"));
                }
            }

            /**
             * @brief Checks for link errors in an OpenGL pipeline.
             * @param passID The ID of the OpenGL pipeline to check.
             * @return True if no linking errors are found, false otherwise.
             */
            bool checkLinkErrors(GLuint passID) const
            {
                GLint isLinked = 0;
                glGetProgramiv(passID, GL_LINK_STATUS, &isLinked);
                if (isLinked == GL_FALSE)
                {
                    GLint maxLength = 0;
                    glGetProgramiv(passID, GL_INFO_LOG_LENGTH, &maxLength);

                    std::vector<GLchar> infoLog(maxLength);
                    glGetProgramInfoLog(passID, maxLength, &maxLength, &infoLog[0]);

                    std::cerr << "Pipeline link error: " << infoLog.data() << std::endl;
                    return false;
                }
                return true;
            }

        private:
            std::shared_ptr<graphic::pipeline::component::pass::IShaderAttacher<graphic::api::OpenGL>> m_attacher;
        };
    }

}