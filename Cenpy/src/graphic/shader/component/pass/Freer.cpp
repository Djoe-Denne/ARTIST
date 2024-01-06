#include <GL/glew.h>
#include <iostream>
#include <graphic/context/PassContext.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/shader/component/pass/Freer.hpp>

namespace cenpy::graphic::shader::opengl::component::pass
{
    /**
     * @class OpenGLPassFreer
     * @brief OpenGL implementation of IPassFreer.
     *
     * Handles the freeing of resources for an OpenGL shader pass, including detaching shaders
     * and deleting the OpenGL program.
     */
    void OpenGLPassFreer::freePass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
    {
        if (!openglContext)
        {
            throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT");
        }

        GLuint programId = openglContext->getProgramId();
        if (programId != 0)
        {
            // Optionally detach shaders before deleting the program
            for (const auto &shader : openglContext->getShaders())
            {
                if (auto oglShaderContext = shader->getContext())
                {
                    glDetachShader(programId, oglShaderContext->getShaderID());
                }
            }

            // Delete the OpenGL program
            glDeleteProgram(programId);
            openglContext->setProgramId(0); // Reset the program ID in the context
        }
    }

}
