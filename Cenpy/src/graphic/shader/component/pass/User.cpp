
#include <GL/glew.h>
#include <format>
#include <graphic/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/shader/component/pass/User.hpp>

namespace cenpy::graphic::shader::opengl::component::pass
{

    void OpenGLPassUser::usePass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
    {
        if (!openglContext)
        {
            // Throw an exception if the context is not valid for OpenGL
            throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_OPENGL_CONTEXT"));
        }

        // Set the OpenGL program for this pass as the current active program
        glUseProgram(openglContext->getProgramId());
    }
}
