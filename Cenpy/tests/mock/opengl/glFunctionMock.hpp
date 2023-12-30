#pragma once

#ifdef __mock_gl__

#include <any>
#include <vector>
#include <GL/glew.h>
#include <EnumClass.hpp>
#include <gmock/gmock.h>

#define glUniform1f cenpy::mock::opengl::glFunctionMock::instance()->glUniform1f_mock
#define glUniform1d cenpy::mock::opengl::glFunctionMock::instance()->glUniform1d_mock
#define glUniform1i cenpy::mock::opengl::glFunctionMock::instance()->glUniform1i_mock
#define glUniform1ui cenpy::mock::opengl::glFunctionMock::instance()->glUniform1ui_mock
#define glUniform2f cenpy::mock::opengl::glFunctionMock::instance()->glUniform2f_mock
#define glUniform3f cenpy::mock::opengl::glFunctionMock::instance()->glUniform3f_mock
#define glUniform4f cenpy::mock::opengl::glFunctionMock::instance()->glUniform4f_mock
#define glUniformMatrix2fv cenpy::mock::opengl::glFunctionMock::instance()->glUniformMatrix2fv_mock
#define glUniformMatrix3fv cenpy::mock::opengl::glFunctionMock::instance()->glUniformMatrix3fv_mock
#define glUniformMatrix4fv cenpy::mock::opengl::glFunctionMock::instance()->glUniformMatrix4fv_mock
#define glUseProgram cenpy::mock::opengl::glFunctionMock::instance()->glUseProgram_mock
#define glValidateProgram cenpy::mock::opengl::glFunctionMock::instance()->glValidateProgram_mock
#define glAttachShader cenpy::mock::opengl::glFunctionMock::instance()->glAttachShader_mock
#define glBindAttribLocation cenpy::mock::opengl::glFunctionMock::instance()->glBindAttribLocation_mock
#define glBlendEquationSeparate cenpy::mock::opengl::glFunctionMock::instance()->glBlendEquationSeparate_mock
#define glCompileShader cenpy::mock::opengl::glFunctionMock::instance()->glCompileShader_mock
#define glCreateProgram cenpy::mock::opengl::glFunctionMock::instance()->glCreateProgram_mock
#define glCreateShader cenpy::mock::opengl::glFunctionMock::instance()->glCreateShader_mock
#define glDeleteProgram cenpy::mock::opengl::glFunctionMock::instance()->glDeleteProgram_mock
#define glDeleteShader cenpy::mock::opengl::glFunctionMock::instance()->glDeleteShader_mock
#define glDetachShader cenpy::mock::opengl::glFunctionMock::instance()->glDetachShader_mock
#define glDisableVertexAttribArray cenpy::mock::opengl::glFunctionMock::instance()->glDisableVertexAttribArray_mock
#define glDrawBuffers cenpy::mock::opengl::glFunctionMock::instance()->glDrawBuffers_mock
#define glEnableVertexAttribArray cenpy::mock::opengl::glFunctionMock::instance()->glEnableVertexAttribArray_mock
#define glGetActiveAttrib cenpy::mock::opengl::glFunctionMock::instance()->glGetActiveAttrib_mock
#define glGetActiveUniform cenpy::mock::opengl::glFunctionMock::instance()->glGetActiveUniform_mock
#define glGetAttachedShaders cenpy::mock::opengl::glFunctionMock::instance()->glGetAttachedShaders_mock
#define glGetAttribLocation cenpy::mock::opengl::glFunctionMock::instance()->glGetAttribLocation_mock
#define glGetProgramInfoLog cenpy::mock::opengl::glFunctionMock::instance()->glGetProgramInfoLog_mock
#define glGetProgramiv cenpy::mock::opengl::glFunctionMock::instance()->glGetProgramiv_mock
#define glGetShaderInfoLog cenpy::mock::opengl::glFunctionMock::instance()->glGetShaderInfoLog_mock
#define glGetShaderSource cenpy::mock::opengl::glFunctionMock::instance()->glGetShaderSource_mock
#define glGetShaderiv cenpy::mock::opengl::glFunctionMock::instance()->glGetShaderiv_mock
#define glGetUniformLocation cenpy::mock::opengl::glFunctionMock::instance()->glGetUniformLocation_mock
#define glGetUniformfv cenpy::mock::opengl::glFunctionMock::instance()->glGetUniformfv_mock
#define glGetUniformiv cenpy::mock::opengl::glFunctionMock::instance()->glGetUniformiv_mock
#define glGetVertexAttribPointerv cenpy::mock::opengl::glFunctionMock::instance()->glGetVertexAttribPointerv_mock
#define glGetVertexAttribdv cenpy::mock::opengl::glFunctionMock::instance()->glGetVertexAttribdv_mock
#define glGetVertexAttribfv cenpy::mock::opengl::glFunctionMock::instance()->glGetVertexAttribfv_mock
#define glGetVertexAttribiv cenpy::mock::opengl::glFunctionMock::instance()->glGetVertexAttribiv_mock
#define glIsProgram cenpy::mock::opengl::glFunctionMock::instance()->glIsProgram_mock
#define glIsShader cenpy::mock::opengl::glFunctionMock::instance()->glIsShader_mock
#define glLinkProgram cenpy::mock::opengl::glFunctionMock::instance()->glLinkProgram_mock
#define glShaderSource cenpy::mock::opengl::glFunctionMock::instance()->glShaderSource_mock
#define glStencilFuncSeparate cenpy::mock::opengl::glFunctionMock::instance()->glStencilFuncSeparate_mock
#define glStencilMaskSeparate cenpy::mock::opengl::glFunctionMock::instance()->glStencilMaskSeparate_mock
#define glStencilOpSeparate cenpy::mock::opengl::glFunctionMock::instance()->glStencilOpSeparate_mock

namespace cenpy::mock::opengl
{
    class glFunctionMock
    {
    public:
        static std::shared_ptr<glFunctionMock> instance()
        {
            static std::shared_ptr<glFunctionMock> instance = std::make_shared<glFunctionMock>();
            return instance;
        }

        static void reset()
        {
            ::testing::Mock::VerifyAndClearExpectations(instance().get());
        }

        glFunctionMock()
        {
            ON_CALL(*this, glGetProgramiv_mock).WillByDefault([this](GLuint program, GLenum pname, GLint *params)
                                                              { (*params) = 1; });

            ON_CALL(*this, glGetShaderiv_mock).WillByDefault([this](GLuint shader, GLenum pname, GLint *params)
                                                             { (*params) = 1; });

            ON_CALL(*this, glGetActiveAttrib_mock).WillByDefault([this](GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
                                                                 {
                // Example mock name
                const char* mockAttribName = "attribut_test";

                // Copy the mock name to the provided 'name' buffer
                strncpy(name, mockAttribName, bufSize);

                // Optionally set the length, if a non-NULL pointer is provided
                if (length != NULL) {
                    *length = strlen(mockAttribName);
                }
                (*size) = 1;
                (*type) = GL_FLOAT; });

            ON_CALL(*this, glGetUniformiv_mock).WillByDefault([this](GLuint program, GLint location, GLint *params)
                                                              { (*params) = 1; });

            ON_CALL(*this, glGetActiveUniform_mock)
                .WillByDefault([this](GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
                               {
                // Example mock name
                const char* mockUniformName = "uniform_test";

                // Copy the mock name to the provided 'name' buffer
                strncpy(name, mockUniformName, bufSize);

                // Optionally set the length, if a non-NULL pointer is provided
                if (length != NULL) {
                    *length = strlen(mockUniformName);
                }
                (*size) = 1;
                (*type) = GL_FLOAT; });

            ON_CALL(*this, glGetUniformLocation_mock).WillByDefault([this](GLuint program, const GLchar *name)
                                                                    { return 1; });

            ON_CALL(*this, glGetAttribLocation_mock).WillByDefault([this](GLuint program, const GLchar *name)
                                                                   { return 1; });

            ON_CALL(*this, glCreateShader_mock).WillByDefault([this](GLenum shaderType)
                                                              { return 1; });

            ON_CALL(*this, glCreateProgram_mock).WillByDefault([this]()
                                                               { return 1; });
        }

        MOCK_METHOD(void, glUniform1f_mock, (GLint, GLfloat));
        MOCK_METHOD(void, glUniform1d_mock, (GLint, GLdouble));
        MOCK_METHOD(void, glUniform1i_mock, (GLint, GLint), ());
        MOCK_METHOD(void, glUniform1ui_mock, (GLint, GLuint), ());
        MOCK_METHOD(void, glUniform2f_mock, (GLint, GLfloat, GLfloat), ());
        MOCK_METHOD(void, glUniform3f_mock, (GLint, GLfloat, GLfloat, GLfloat), ());
        MOCK_METHOD(void, glUniform4f_mock, (GLint, GLfloat, GLfloat, GLfloat, GLfloat), ());
        MOCK_METHOD(void, glUniformMatrix2fv_mock, (GLint, GLsizei, GLboolean, const GLfloat *), ());
        MOCK_METHOD(void, glUniformMatrix3fv_mock, (GLint, GLsizei, GLboolean, const GLfloat *), ());
        MOCK_METHOD(void, glUniformMatrix4fv_mock, (GLint, GLsizei, GLboolean, const GLfloat *), ());
        MOCK_METHOD(void, glUseProgram_mock, (GLuint), ());
        MOCK_METHOD(void, glValidateProgram_mock, (GLuint), ());
        MOCK_METHOD(void, glAttachShader_mock, (GLuint, GLuint), ());
        MOCK_METHOD(void, glBindAttribLocation_mock, (GLuint, GLuint, const GLchar *), ());
        MOCK_METHOD(void, glBlendEquationSeparate_mock, (GLenum, GLenum), ());
        MOCK_METHOD(void, glCompileShader_mock, (GLuint), ());
        MOCK_METHOD(GLuint, glCreateProgram_mock, (), ());
        MOCK_METHOD(GLuint, glCreateShader_mock, (GLenum), ());
        MOCK_METHOD(void, glDeleteProgram_mock, (GLuint), ());
        MOCK_METHOD(void, glDeleteShader_mock, (GLuint), ());
        MOCK_METHOD(void, glDetachShader_mock, (GLuint, GLuint), ());
        MOCK_METHOD(void, glDisableVertexAttribArray_mock, (GLuint), ());
        MOCK_METHOD(void, glDrawBuffers_mock, (GLsizei, const GLenum *), ());
        MOCK_METHOD(void, glEnableVertexAttribArray_mock, (GLuint), ());
        MOCK_METHOD(void, glGetActiveAttrib_mock, (GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *), ());
        MOCK_METHOD(void, glGetActiveUniform_mock, (GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *), ());
        MOCK_METHOD(void, glGetAttachedShaders_mock, (GLuint, GLsizei, GLsizei *, GLuint *), ());
        MOCK_METHOD(GLint, glGetAttribLocation_mock, (GLuint, const GLchar *), ());
        MOCK_METHOD(void, glGetProgramInfoLog_mock, (GLuint, GLsizei, GLsizei *, GLchar *), ());
        MOCK_METHOD(void, glGetProgramiv_mock, (GLuint, GLenum, GLint *), ());
        MOCK_METHOD(void, glGetShaderInfoLog_mock, (GLuint, GLsizei, GLsizei *, GLchar *), ());
        MOCK_METHOD(void, glGetShaderSource_mock, (GLuint, GLsizei, GLsizei *, GLchar *), ());
        MOCK_METHOD(void, glGetShaderiv_mock, (GLuint, GLenum, GLint *), ());
        MOCK_METHOD(GLint, glGetUniformLocation_mock, (GLuint, const GLchar *), ());
        MOCK_METHOD(void, glGetUniformfv_mock, (GLuint, GLint, GLfloat *), ());
        MOCK_METHOD(void, glGetUniformiv_mock, (GLuint, GLint, GLint *), ());
        MOCK_METHOD(void, glGetVertexAttribPointerv_mock, (GLuint, GLenum, void **), ());
        MOCK_METHOD(void, glGetVertexAttribdv_mock, (GLuint, GLenum, GLdouble *), ());
        MOCK_METHOD(void, glGetVertexAttribfv_mock, (GLuint, GLenum, GLfloat *), ());
        MOCK_METHOD(void, glGetVertexAttribiv_mock, (GLuint, GLenum, GLint *), ());
        MOCK_METHOD(GLboolean, glIsProgram_mock, (GLuint), ());
        MOCK_METHOD(GLboolean, glIsShader_mock, (GLuint), ());
        MOCK_METHOD(void, glLinkProgram_mock, (GLuint), ());
        MOCK_METHOD(void, glShaderSource_mock, (GLuint, GLsizei, const GLchar *const *, const GLint *), ());
        MOCK_METHOD(void, glStencilFuncSeparate_mock, (GLenum, GLenum, GLint, GLuint), ());
        MOCK_METHOD(void, glStencilMaskSeparate_mock, (GLenum, GLuint), ());
        MOCK_METHOD(void, glStencilOpSeparate_mock, (GLenum, GLenum, GLenum, GLenum), ());
    };
} // namespace cenpy::mock::opengl

#endif // __mock_gl__