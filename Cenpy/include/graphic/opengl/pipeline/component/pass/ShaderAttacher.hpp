#pragma once

#include <GL/glew.h>
#include <memory>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/profile/Pass.hpp>

namespace cenpy::graphic::opengl::pipeline::component::pass
{
    /**
     * @class OpenGLPassAttacher
     * @brief OpenGL implementation of IShaderAttacher.
     *
     * This class implements the shader attaching process for an OpenGL shader pass.
     * It attaches all shaders within the given PassContext to an OpenGL pipeline.
     */
    template <auto PROFILE>
    class OpenGLShaderAttacher
    {
    };

    template <>
    class OpenGLShaderAttacher<graphic::opengl::profile::Pass::Classic>
    {
    public:
        /**
         * @brief Attach shaders to the pass in OpenGL context.
         * @param context PassContext containing pass details specific to OpenGL.
         *
         * This implementation casts the generic PassContext to an OpenGLPassContext,
         * and attaches each shader to the OpenGL pipeline. If the context casting fails
         * or if any shader context is invalid, an exception is thrown.
         */
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

            for (const auto &shader : openglContext->getShaders())
            {
                glAttachShader(passID, shader->getContext()->getShaderID());
            }
        }
    };

}
