#include <GL/glew.h>
#include <graphic/context/PassContext.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>
#include <common/exception/TraceableException.hpp>

namespace cenpy::graphic::shader::opengl::component::pass
{
    void OpenGLShaderAttacher::attachShaders(std::shared_ptr<typename cenpy::graphic::api::OpenGL::PassContext> openglContext)
    {
        if (!openglContext)
        {
            throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT");
        }

        GLuint programId = openglContext->getProgramId();
        if (programId == 0)
        {
            throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::INVALID_PROGRAM_ID");
        }

        for (const auto &shader : openglContext->getShaders())
        {
            if (auto oglShaderContext = std::dynamic_pointer_cast<graphic::opengl::context::OpenGLShaderContext>(shader->getContext()))
            {
                glAttachShader(programId, oglShaderContext->getShaderID());
            }
            else
            {
                throw common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::INVALID_SHADER_CONTEXT");
            }
        }
    }

}
