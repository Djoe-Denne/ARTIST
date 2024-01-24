#pragma once

#include <memory>
#include <graphic/Api.hpp>
#include <GL/glew.h>
#include <iostream>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/opengl/profile/Pass.hpp>

namespace cenpy::graphic::opengl::pipeline::component::pass
{
    /**
     * @class OpenGLPassFreer
     * @brief OpenGL implementation of IPassFreer.
     *
     * Handles the freeing of resources for an OpenGL shader pass, including detaching shaders
     * and deleting the OpenGL pipeline.
     */
    template <auto PROFILE>
    class OpenGLPassFreer
    {
    };

    template <>
    class OpenGLPassFreer<graphic::opengl::profile::Pass::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
        {

            if (!openglContext)
            {
                throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT");
            }

            GLuint passID = openglContext->getPassID();
            if (passID != 0)
            {
                // Optionally detach shaders before deleting the pipeline
                for (const auto &shader : openglContext->getShaders())
                {
                    if (auto oglShaderContext = shader->getContext())
                    {
                        glDetachShader(passID, oglShaderContext->getShaderID());
                    }
                }

                // Delete the OpenGL pipeline
                glDeleteProgram(passID);
                openglContext->setPassID(0); // Reset the pipeline ID in the context
            }
        }
    };
}
