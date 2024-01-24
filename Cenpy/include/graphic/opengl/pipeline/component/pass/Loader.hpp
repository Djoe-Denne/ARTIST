#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/pipeline/component/pass/ShaderAttacher.hpp>
#include <graphic/opengl/profile/Pass.hpp>

namespace cenpy::graphic::opengl::pipeline::component::pass
{
    template <auto PROFILE>
    class OpenGLLoader
    {
    };

    template <>
    class OpenGLLoader<graphic::opengl::profile::Pass::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
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
            cenpy::graphic::api::OpenGL::PassContext::ShaderAttacher<graphic::opengl::profile::Pass::Classic>::on(openglContext);

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
        static bool
        checkLinkErrors(GLuint passID)
        {
            GLint isLinked = 0;
            glGetProgramiv(passID, GL_LINK_STATUS, &isLinked);
            if (isLinked == GL_FALSE)
            {
                GLint maxLength = 10000;
                glGetProgramiv(passID, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetProgramInfoLog(passID, maxLength, &maxLength, &infoLog[0]);

                std::cerr << "Pipeline link error: " << infoLog.data() << std::endl;
                return false;
            }
            return true;
        }
    };
}
