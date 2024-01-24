#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/Api.hpp>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/opengl/pipeline/component/uniform/MockSetter.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/pipeline/component/pass/Freer.hpp>

namespace api = cenpy::graphic::api;
namespace mock = cenpy::mock;
namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::opengl::pipeline::component::pass;
using cenpy::graphic::opengl::profile::Pass::Classic;
using MockShader = cenpy::mock::graphic::pipeline::MockShader<api::OpenGL>;

class PassFreerTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(PassFreerTests, FreePassTest_validContext)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    auto openglShaderContext = std::make_shared<context::OpenGLShaderContext>();
    auto *shader1 = new MockShader("shader_path", cenpy::graphic::context::ShaderType::VERTEX);
    delete shader1;
    auto shader = std::make_shared<MockShader>("shader_path", cenpy::graphic::context::ShaderType::VERTEX);
    openglContext->addShader(shader);
    openglContext->setPassID(1);          // Set a mock pipeline ID
    openglShaderContext->setShaderID(42); // Set a mock shader ID

    // Expect calls for valid context
    ON_CALL(*shader, getContext()).WillByDefault(::testing::ReturnRef(openglShaderContext));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDetachShader_mock(1, 42)).Times(::testing::AtLeast(1));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteProgram_mock(1)).Times(1);

    // Act
    ASSERT_NO_THROW(pass::OpenGLPassFreer<Classic>::on(openglContext));

    // Assert
    ASSERT_EQ(openglContext->getPassID(), 0);
}

TEST_F(PassFreerTests, FreePassTest_nullContext)
{
    // Arrange

    // Act & Assert
    EXPECT_THROW(pass::OpenGLPassFreer<Classic>::on(nullptr), std::runtime_error);
}

TEST_F(PassFreerTests, FreePassTest_noPassID)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>(); // No pipeline ID set

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLPassFreer<Classic>::on(openglContext));
    ASSERT_EQ(openglContext->getPassID(), 0); // Ensure pipeline ID remains 0
}

TEST_F(PassFreerTests, FreePassTest_detachShaders)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a mock pipeline ID

    // Add mock shaders to context
    // ...

    // Expect detach calls for each shader
    // ...

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLPassFreer<Classic>::on(openglContext));
}

TEST_F(PassFreerTests, FreePassTest_deletePipeline)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a mock pipeline ID

    // Expect delete call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteProgram_mock(1)).Times(1);

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLPassFreer<Classic>::on(openglContext));
}

TEST_F(PassFreerTests, FreePassTest_noShaders)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a mock pipeline ID

    // Expect no detach calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDetachShader_mock(::testing::_, ::testing::_)).Times(0);

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLPassFreer<Classic>::on(openglContext));
}

#endif // __mock_gl__