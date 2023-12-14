#ifdef __mock_gl__
#include <any>
#include <iostream>
#include <gtest/gtest.h>

#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/Uniform.hpp>

namespace shader = cenpy::graphic::shader::opengl;
namespace mock = cenpy::mock::opengl;

class UniformTest : public ::testing::Test
{
public:
};

TEST_F(UniformTest, SetFloatUniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(3.14f));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM1F);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 3.14f);
}

TEST_F(UniformTest, SetDoubleUniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_DOUBLE, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(3.14));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM1D);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLdouble>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 3.14);
}

TEST_F(UniformTest, SetIntUniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_INT, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(42));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM1I);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 42);
}

TEST_F(UniformTest, SetUnsignedIntUniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_UNSIGNED_INT, 1);
    unsigned int value = 42;

    // Act
    ASSERT_NO_THROW(uniform.set(value));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM1UI);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLuint>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 42);
}

TEST_F(UniformTest, SetVec2Uniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT_VEC2, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(glm::vec2(3.14f, 42.0f)));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM2F);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 3.14f);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[2]), 42.0f);
}

TEST_F(UniformTest, SetVec3Uniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT_VEC3, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(glm::vec3(3.14f, 42.0f, 1.0f)));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM3F);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 3.14f);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[2]), 42.0f);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[3]), 1.0f);
}

TEST_F(UniformTest, SetVec4Uniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT_VEC4, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(glm::vec4(3.14f, 42.0f, 1.0f, 0.0f)));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORM4F);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 3.14f);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[2]), 42.0f);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[3]), 1.0f);
    EXPECT_EQ(std::any_cast<GLfloat>(mock::glFunctionMock::m_lastGLFunctionArgs[4]), 0.0f);
}

TEST_F(UniformTest, SetMat2Uniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT_MAT2, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(glm::mat2(3.14f, 42.0f, 1.0f, 0.0f)));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORMMATRIX2FV);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLsizei>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 1);
    EXPECT_EQ(std::any_cast<GLboolean>(mock::glFunctionMock::m_lastGLFunctionArgs[2]), GL_FALSE);
}

TEST_F(UniformTest, SetMat3Uniform)
{
    // Arrange
    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT_MAT3, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(glm::mat3(3.14f, 42.0f, 1.0f, 0.0f, 3.14f, 42.0f, 1.0f, 0.0f, 3.14f)));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORMMATRIX3FV);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLsizei>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 1);
    EXPECT_EQ(std::any_cast<GLboolean>(mock::glFunctionMock::m_lastGLFunctionArgs[2]), GL_FALSE);
}

TEST_F(UniformTest, SetMat4Uniform)
{
    // Arrange

    GLuint location = 42;
    shader::Uniform uniform(location, GL_FLOAT_MAT4, 1);

    // Act
    ASSERT_NO_THROW(uniform.set(glm::mat4(3.14f, 42.0f, 1.0f, 0.0f, 3.14f, 42.0f, 1.0f, 0.0f, 3.14f, 42.0f, 1.0f, 0.0f, 3.14f, 42.0f, 1.0f, 0.0f)));

    // Assert
    EXPECT_EQ(mock::glFunctionMock::m_lastGLFunction, mock::GLfunctionEnum::GL_UNIFORMMATRIX4FV);
    EXPECT_EQ(std::any_cast<GLint>(mock::glFunctionMock::m_lastGLFunctionArgs[0]), location);
    EXPECT_EQ(std::any_cast<GLsizei>(mock::glFunctionMock::m_lastGLFunctionArgs[1]), 1);
    EXPECT_EQ(std::any_cast<GLboolean>(mock::glFunctionMock::m_lastGLFunctionArgs[2]), GL_FALSE);
}

#endif // __mock_gl__
