#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/Api.hpp>
#include <opengl/glFunctionMock.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/context/ShaderContext.hpp>
#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/opengl/pipeline/component/pass/ShaderAttacher.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::opengl::pipeline::component::pass;
namespace mock = cenpy::mock;
namespace shader = mock::graphic::pipeline;
using MockShader = cenpy::mock::graphic::pipeline::MockShader<cenpy::graphic::api::OpenGL>;
using cenpy::graphic::opengl::profile::Pass::Classic;
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
    openglContext->setPassID(1);      // Set a valid pipeline ID
    openglContext->addShader(shader); // Add a mock shader
    shaderContext->setShaderID(42);   // Set a mock shader ID

    // Expect calls for valid context
    EXPECT_CALL(*shader, getContext()).WillRepeatedly(::testing::ReturnRef(shaderContext));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glAttachShader_mock(1, 42)).Times(1);

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLShaderAttacher<Classic>::on(openglContext));
}

TEST_F(ShaderAttacherTests, AttachShaders_NullContext)
{
    // Arrange

    // Act & Assert
    expectSpecificError([]()
                        { pass::OpenGLShaderAttacher<Classic>::on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT"));
}

TEST_F(ShaderAttacherTests, AttachShaders_InvalidPassID)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>(); // No pipeline ID set

    // Act & Assert
    expectSpecificError([&openglContext]()
                        { pass::OpenGLShaderAttacher<Classic>::on(openglContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::INVALID_PROGRAM_ID"));
}

TEST_F(ShaderAttacherTests, AttachShaders_NoShaders)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a valid pipeline ID

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLShaderAttacher<Classic>::on(openglContext));
}

#endif // __mock_gl__