#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/Api.hpp>
#include <opengl/glFunctionMock.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/context/ShaderContext.hpp>
#include <graphic/shader/MockShader.hpp>
#include <graphic/shader/component/pass/ShaderAttacher.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::shader::opengl::component::pass;
namespace mock = cenpy::mock;
namespace shader = mock::graphic::shader;
using MockShader = cenpy::mock::graphic::shader::MockShader<cenpy::graphic::api::OpenGL>;
using cenpy::test::utils::expectSpecificError;

class ShaderAttacherTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(ShaderAttacherTests, AttachShaders_ValidContext)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    auto shaderContext = std::make_shared<context::OpenGLShaderContext>();
    auto shader = std::make_shared<MockShader>();
    openglContext->setProgramId(1);   // Set a valid program ID
    openglContext->addShader(shader); // Add a mock shader
    shaderContext->setShaderID(42);   // Set a mock shader ID
    pass::OpenGLShaderAttacher shaderAttacher;

    // Expect calls for valid context
    EXPECT_CALL(*shader, getContext()).WillRepeatedly(::testing::ReturnRef(shaderContext));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glAttachShader_mock(1, 42)).Times(1);

    // Act & Assert
    ASSERT_NO_THROW(shaderAttacher.attachShaders(openglContext));
}

TEST_F(ShaderAttacherTests, AttachShaders_NullContext)
{
    // Arrange
    pass::OpenGLShaderAttacher shaderAttacher;

    // Act & Assert
    expectSpecificError([&shaderAttacher]()
                        { shaderAttacher.attachShaders(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT"));
}

TEST_F(ShaderAttacherTests, AttachShaders_InvalidProgramId)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>(); // No program ID set
    pass::OpenGLShaderAttacher shaderAttacher;

    // Act & Assert
    expectSpecificError([&openglContext, &shaderAttacher]()
                        { shaderAttacher.attachShaders(openglContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::INVALID_PROGRAM_ID"));
}

TEST_F(ShaderAttacherTests, AttachShaders_NoShaders)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setProgramId(1); // Set a valid program ID
    pass::OpenGLShaderAttacher shaderAttacher;

    // Act & Assert
    ASSERT_NO_THROW(shaderAttacher.attachShaders(openglContext));
}

#endif // __mock_gl__