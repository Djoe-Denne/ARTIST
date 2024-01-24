#pragma once

#include <GL/glew.h>
#include <format>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/opengl/pipeline/component/pass/User.hpp>
#include <graphic/opengl/profile/Pass.hpp>

namespace cenpy::graphic::opengl::pipeline::component::pass
{
    /**
     * @class OpenGLPassUser
     * @brief OpenGL implementation of IPassUser.
     *
     * Handles the activation of a shader pass in an OpenGL context. This includes setting the
     * current OpenGL pipeline to the one associated with the shader pass.
     */
    template <auto PROFILE>
    class OpenGLPassUser
    {
    };

    template <>
    class OpenGLPassUser<graphic::opengl::profile::Pass::Classic>
    {
    public:
        static void on(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
        {
            if (!openglContext)
            {
                // Throw an exception if the context is not valid for OpenGL
                throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_OPENGL_CONTEXT"));
            }

            // Set the OpenGL pipeline for this pass as the current active pipeline
            glUseProgram(openglContext->getPassID());
        }
    };
}
