#ifdef __mock_gl__
#include <any>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/Uniform.hpp>

namespace shader = cenpy::graphic::shader::opengl;
namespace mock = cenpy::mock::opengl;

class UniformTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        mock::glFunctionMock::reset();
    }
};

TEST_F(UniformTest, SetFloatUniform)
{
    // Arrange
    GLuint location = 42;
    GLfloat value = 3.14f;
    shader::Uniform uniform(location, GL_FLOAT, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform1f_mock(location, value))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetDoubleUniform)
{
    // Arrange
    GLuint location = 42;
    GLdouble value = 3.14;
    shader::Uniform uniform(location, GL_DOUBLE, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform1d_mock(location, value))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetIntUniform)
{
    // Arrange
    GLuint location = 42;
    GLint value = 42;
    shader::Uniform uniform(location, GL_INT, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform1i_mock(location, value))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetUIntUniform)
{
    // Arrange
    GLuint location = 42;
    GLuint value = 42;
    shader::Uniform uniform(location, GL_UNSIGNED_INT, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform1ui_mock(location, value))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetVec2Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::vec2 value(3.14f, 2.71f);
    shader::Uniform uniform(location, GL_FLOAT_VEC2, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform2f_mock(location, value[0], value[1]))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetVec3Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::vec3 value(3.14f, 2.71f, 1.41f);
    shader::Uniform uniform(location, GL_FLOAT_VEC3, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform3f_mock(location, value[0], value[1], value[2]))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetVec4Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::vec4 value(3.14f, 2.71f, 1.41f, 1.61f);
    shader::Uniform uniform(location, GL_FLOAT_VEC4, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform4f_mock(location, value[0], value[1], value[2], value[3]))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetMat2Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::mat2 value(3.14f, 2.71f, 1.41f, 1.61f);
    shader::Uniform uniform(location, GL_FLOAT_MAT2, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniformMatrix2fv_mock(location, 1, GL_FALSE, ::testing::_))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetMat3Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::mat3 value(3.14f, 2.71f, 1.41f, 1.61f, 2.71f, 1.41f, 1.61f, 2.71f, 1.41f);
    shader::Uniform uniform(location, GL_FLOAT_MAT3, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniformMatrix3fv_mock(location, 1, GL_FALSE, ::testing::_))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetMat4Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::mat4 value(3.14f, 2.71f, 1.41f, 1.61f, 2.71f, 1.41f, 1.61f, 2.71f, 1.41f, 1.61f, 2.71f, 1.41f, 1.61f, 2.71f, 1.41f, 1.61f);
    shader::Uniform uniform(location, GL_FLOAT_MAT4, 1);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniformMatrix4fv_mock(location, 1, GL_FALSE, ::testing::_))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

#endif // __mock_gl__
