#pragma once

#ifdef __mock_gl__

#include <any>
#include <vector>
#include <GL/glew.h>
#include <EnumClass.hpp>

#define glUniform1f cenpy::mock::opengl::glFunctionMock::glUniform1f_mock
#define glUniform1d cenpy::mock::opengl::glFunctionMock::glUniform1d_mock
#define glUniform1i cenpy::mock::opengl::glFunctionMock::glUniform1i_mock
#define glUniform1ui cenpy::mock::opengl::glFunctionMock::glUniform1ui_mock
#define glUniform2f cenpy::mock::opengl::glFunctionMock::glUniform2f_mock
#define glUniform3f cenpy::mock::opengl::glFunctionMock::glUniform3f_mock
#define glUniform4f cenpy::mock::opengl::glFunctionMock::glUniform4f_mock
#define glUniformMatrix2fv cenpy::mock::opengl::glFunctionMock::glUniformMatrix2fv_mock
#define glUniformMatrix3fv cenpy::mock::opengl::glFunctionMock::glUniformMatrix3fv_mock
#define glUniformMatrix4fv cenpy::mock::opengl::glFunctionMock::glUniformMatrix4fv_mock

namespace cenpy::mock::opengl
{
    enum class GLfunctionEnum
    {
        GL_UNIFORM1F,
        GL_UNIFORM1D,
        GL_UNIFORM1I,
        GL_UNIFORM1UI,
        GL_UNIFORM2F,
        GL_UNIFORM3F,
        GL_UNIFORM4F,
        GL_UNIFORMMATRIX2FV,
        GL_UNIFORMMATRIX3FV,
        GL_UNIFORMMATRIX4FV
    };

    using GLfunction = EnumClass<GLfunctionEnum>;

    class glFunctionMock
    {
    public:
        static GLfunction m_lastGLFunction;
        static std::vector<std::any> m_lastGLFunctionArgs;

        static void glUniform1f_mock(GLint location, const GLfloat &value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM1F;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(value);
        }

        static void glUniform1d_mock(GLint location, const GLdouble &value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM1D;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(value);
        }

        static void glUniform1i_mock(GLint location, const GLint &value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM1I;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(value);
        }

        static void glUniform1ui_mock(GLint location, const GLuint &value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM1UI;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(value);
        }

        static void glUniform2f_mock(GLint location, const GLfloat &v0, const GLfloat &v1)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM2F;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(v0);
            m_lastGLFunctionArgs.push_back(v1);
        }

        static void glUniform3f_mock(GLint location, const GLfloat &v0, const GLfloat &v1, const GLfloat &v2)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM3F;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(v0);
            m_lastGLFunctionArgs.push_back(v1);
            m_lastGLFunctionArgs.push_back(v2);
        }

        static void glUniform4f_mock(GLint location, const GLfloat &v0, const GLfloat &v1, const GLfloat &v2, const GLfloat &v3)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORM4F;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(v0);
            m_lastGLFunctionArgs.push_back(v1);
            m_lastGLFunctionArgs.push_back(v2);
            m_lastGLFunctionArgs.push_back(v3);
        }

        static void glUniformMatrix2fv_mock(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORMMATRIX2FV;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(count);
            m_lastGLFunctionArgs.push_back(transpose);
            m_lastGLFunctionArgs.push_back(value);
        }

        static void glUniformMatrix3fv_mock(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORMMATRIX3FV;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(count);
            m_lastGLFunctionArgs.push_back(transpose);
            m_lastGLFunctionArgs.push_back(value);
        }

        static void glUniformMatrix4fv_mock(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
        {
            m_lastGLFunction = GLfunctionEnum::GL_UNIFORMMATRIX4FV;
            m_lastGLFunctionArgs.clear();
            m_lastGLFunctionArgs.push_back(location);
            m_lastGLFunctionArgs.push_back(count);
            m_lastGLFunctionArgs.push_back(transpose);
            m_lastGLFunctionArgs.push_back(value);
        }
    };
    GLfunction glFunctionMock::m_lastGLFunction = GLfunctionEnum::GL_UNIFORM1F;
    std::vector<std::any> glFunctionMock::m_lastGLFunctionArgs = {};

} // namespace cenpy::mock::opengl

#endif // __mock_gl__