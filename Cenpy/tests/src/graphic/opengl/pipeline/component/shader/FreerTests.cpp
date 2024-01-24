#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/profile/Shader.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/pipeline/component/shader/Freer.hpp>

namespace mock = cenpy::mock;
namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::opengl::context;
namespace shader = cenpy::graphic::opengl::pipeline::component::shader;
using cenpy::graphic::opengl::profile::Shader::Classic;

class FreerTests : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(FreerTests, FreeShader_freeOnGPU)
{
    // Arrange
    auto shaderContext = std::make_shared<context::OpenGLShaderContext>();
    shaderContext->setShaderID(666);

    // Except calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteShader_mock(666)).Times(1);

    // Act
    ASSERT_NO_THROW(shader::OpenGLShaderFreer<Classic>::on(shaderContext));

    // Assert
}

TEST_F(FreerTests, FreeShader_setShaderIDToZero)
{
    // Arrange
    auto shaderContext = std::make_shared<context::OpenGLShaderContext>();
    shaderContext->setShaderID(666);

    // Act
    ASSERT_NO_THROW(shader::OpenGLShaderFreer<Classic>::on(shaderContext));

    // Assert
    ASSERT_EQ(shaderContext->getShaderID(), 0);
}

TEST_F(FreerTests, FreeShader_doNothing_whenShaderIDIsZero)
{
    // Arrange
    auto shaderContext = std::make_shared<context::OpenGLShaderContext>();
    shaderContext->setShaderID(0);

    // Except calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteShader_mock(::testing::_)).Times(0);

    // Act
    ASSERT_NO_THROW(shader::OpenGLShaderFreer<Classic>::on(shaderContext));

    // Assert
    ASSERT_EQ(shaderContext->getShaderID(), 0);
}

#endif // __mock_gl__