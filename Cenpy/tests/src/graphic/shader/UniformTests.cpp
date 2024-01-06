#ifdef __mock_gl__
#include <any>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <graphic/Api.hpp>
#include <opengl/glFunctionMock.hpp>
#include <graphic/shader/Uniform.hpp>
#include <graphic/context/UniformContext.hpp>

namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::opengl::context;
namespace shader = cenpy::graphic::shader;
namespace mock = cenpy::mock::opengl;

class UniformTest : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::glFunctionMock::reset();
    }
};

TEST_F(UniformTest, SetFloatUniform)
{
    // Arrange
    GLuint location = 42;
    GLfloat value = 3.14f;
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(1.0f);

    shader::Uniform<api::OpenGL> uniform(uniformContext);

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
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(1.0);

    shader::Uniform<api::OpenGL> uniform(uniformContext);

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
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(1);

    shader::Uniform<api::OpenGL> uniform(uniformContext);

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

    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue((GLuint)1);

    shader::Uniform<api::OpenGL> uniform(uniformContext);

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
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(glm::vec2(1.0f, 1.0f));

    shader::Uniform<api::OpenGL> uniform(uniformContext);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform2fv_mock(location, 1, &value[0]))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetVec3Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::vec3 value(3.14f, 2.71f, 1.41f);
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(glm::vec3(1.0f, 1.0f, 1.0f));

    shader::Uniform<api::OpenGL> uniform(uniformContext);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform3fv_mock(location, 1, &value[0]))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetVec4Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::vec4 value(3.14f, 2.71f, 1.41f, 1.61f);
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    shader::Uniform<api::OpenGL> uniform(uniformContext);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniform4fv_mock(location, 1, &value[0]))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

TEST_F(UniformTest, SetMat2Uniform)
{
    // Arrange
    GLuint location = 42;
    glm::mat2 value(3.14f, 2.71f, 1.41f, 1.61f);
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(glm::mat2(1.0f, 1.0f, 1.0f, 1.0f));

    shader::Uniform<api::OpenGL> uniform(uniformContext);

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
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(glm::mat3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                       1.0f, 1.0f, 1.0f));

    shader::Uniform<api::OpenGL> uniform(uniformContext);

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
    auto uniformContext = std::make_shared<api::OpenGL::UniformContext>();
    uniformContext->setUniformID(location);
    uniformContext->setValue(glm::mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0, 1.0f, 1.0f, 1.0f));

    shader::Uniform<api::OpenGL> uniform(uniformContext);

    // Expected call
    EXPECT_CALL(*mock::glFunctionMock::instance(), glUniformMatrix4fv_mock(location, 1, GL_FALSE, ::testing::_))
        .Times(1);

    // Act
    ASSERT_NO_THROW(uniform.set(value));
}

#endif // __mock_gl__
