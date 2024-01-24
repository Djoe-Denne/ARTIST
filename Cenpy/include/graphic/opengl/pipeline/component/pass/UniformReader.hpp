#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/opengl/profile/Pass.hpp>

namespace cenpy::graphic::opengl::pipeline::component::pass
{
    /**
     * @class OpenGLUniformReader
     * @brief OpenGL implementation of the IPassUniformReader interface.
     *
     * This class specializes in reading uniform variables from an OpenGL shader pipeline.
     * It extracts the details of each uniform and populates them into the provided map.
     */
    template <auto PROFILE>
    class OpenGLPassUniformReader
    {
    };

    template <>
    class OpenGLPassUniformReader<graphic::opengl::profile::Pass::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
        {
            if (!openglContext)
            {
                throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT");
            }

            GLuint passID = openglContext->getPassID();
            if (passID == 0)
            {
                throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::INVALID_PROGRAM_ID");
            }

            GLint numUniforms = 0;
            glGetProgramiv(passID, GL_ACTIVE_UNIFORMS, &numUniforms);

            for (GLint i = 0; i < numUniforms; ++i)
            {
                char uniformName[256];
                GLsizei nameLength = 0;
                GLsizei size = 0;
                GLenum type = 0;
                glGetActiveUniform(passID, i, sizeof(uniformName), &nameLength, &size, &type, uniformName);

                GLuint location = glGetUniformLocation(passID, uniformName);

                // Create a Uniform object and store it in the map
                auto uniformContext = std::make_shared<graphic::api::OpenGL::UniformContext>();
                uniformContext->setUniformID(location);
                uniformContext->setGLType(type);
                // Known limitation of OpenGL: Uniforms profile are driven by Pass profile
                auto uniform = std::make_shared<graphic::pipeline::Uniform<graphic::api::OpenGL>>(uniformContext);
                openglContext->addUniform(std::string(uniformName), uniform);
            }
        }
    };
}
