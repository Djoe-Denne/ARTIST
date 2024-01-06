#include <GL/glew.h>
#include <graphic/context/PassContext.hpp>
#include <common/exception/TraceableException.hpp>
#include <graphic/shader/Uniform.hpp>
#include <graphic/shader/component/pass/UniformReader.hpp>

namespace cenpy::graphic::shader::opengl::component::pass
{
    void OpenGLPassUniformReader::readUniforms(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
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

        GLint numUniforms = 0;
        glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &numUniforms);

        for (GLint i = 0; i < numUniforms; ++i)
        {
            char uniformName[256];
            GLsizei nameLength = 0;
            GLsizei size = 0;
            GLenum type = 0;
            glGetActiveUniform(programId, i, sizeof(uniformName), &nameLength, &size, &type, uniformName);

            GLuint location = glGetUniformLocation(programId, uniformName);

            // Create a Uniform object and store it in the map
            auto uniformContext = std::make_shared<graphic::api::OpenGL::UniformContext>();
            uniformContext->setUniformID(location);
            uniformContext->setGLType(type);
            std::shared_ptr<graphic::shader::Uniform<graphic::api::OpenGL>> uniform = std::make_shared<graphic::shader::Uniform<graphic::api::OpenGL>>(uniformContext);
            openglContext->addUniform(std::string(uniformName), uniform);
        }
    }
}
