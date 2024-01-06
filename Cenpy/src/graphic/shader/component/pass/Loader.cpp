#include <GL/glew.h>
#include <graphic/context/PassContext.hpp>
#include <graphic/shader/component/pass/Loader.hpp>

namespace cenpy::graphic::shader::opengl::component::pass
{
    void OpenGLPassLoader::loadPass(std::shared_ptr<typename graphic::api::OpenGL::PassContext> openglContext)
    {
        if (!openglContext)
        {
            throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_OPENGL_CONTEXT"));
        }

        GLuint programId = glCreateProgram();
        if (programId == 0)
        {
            throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM_CREATION_FAILED\nFailed to create shader program."));
        }

        // Save the created program ID in the context
        openglContext->setProgramId(programId);
        m_attacher->attachShaders(openglContext);

        // Link the program
        glLinkProgram(programId);

        if (!checkLinkErrors(programId))
        {
            glDeleteProgram(programId);
            throw common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::LINK_FAILED"));
        }
    }

    /**
     * @brief Checks for link errors in an OpenGL program.
     * @param programId The ID of the OpenGL program to check.
     * @return True if no linking errors are found, false otherwise.
     */
    bool OpenGLPassLoader::checkLinkErrors(GLuint programId) const
    {
        GLint isLinked = 0;
        glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

            std::cerr << "Program link error: " << infoLog.data() << std::endl;
            return false;
        }
        return true;
    }
}
