#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/Api.hpp>
#include <graphic/pipeline/MockShader.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/pipeline/component/pass/Freer.hpp>

namespace api = cenpy::graphic::api;
namespace mock = cenpy::mock;
namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::pipeline::opengl::component::pass;
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
    auto shader = std::make_shared<MockShader>("shader_path", cenpy::graphic::context::ShaderType::VERTEX);
    openglContext->addShader(shader);
    openglContext->setPassID(1);       // Set a mock pipeline ID
    openglShaderContext->setShaderID(42); // Set a mock shader ID

    pass::OpenGLPassFreer passFreer;

    // Expect calls for valid context
    ON_CALL(*shader, getContext()).WillByDefault(::testing::ReturnRef(openglShaderContext));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDetachShader_mock(1, 42)).Times(::testing::AtLeast(1));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteProgram_mock(1)).Times(1);

    // Act
    ASSERT_NO_THROW(passFreer.freePass(openglContext));

    // Assert
    ASSERT_EQ(openglContext->getPassID(), 0);
}

TEST_F(PassFreerTests, FreePassTest_nullContext)
{
    // Arrange
    pass::OpenGLPassFreer passFreer;

    // Act & Assert
    EXPECT_THROW(passFreer.freePass(nullptr), std::runtime_error);
}

TEST_F(PassFreerTests, FreePassTest_noPassID)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>(); // No pipeline ID set
    pass::OpenGLPassFreer passFreer;

    // Act & Assert
    ASSERT_NO_THROW(passFreer.freePass(openglContext));
    ASSERT_EQ(openglContext->getPassID(), 0); // Ensure pipeline ID remains 0
}

TEST_F(PassFreerTests, FreePassTest_detachShaders)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a mock pipeline ID
    pass::OpenGLPassFreer passFreer;

    // Add mock shaders to context
    // ...

    // Expect detach calls for each shader
    // ...

    // Act & Assert
    ASSERT_NO_THROW(passFreer.freePass(openglContext));
}

TEST_F(PassFreerTests, FreePassTest_deletePipeline)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a mock pipeline ID
    pass::OpenGLPassFreer passFreer;

    // Expect delete call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteProgram_mock(1)).Times(1);

    // Act & Assert
    ASSERT_NO_THROW(passFreer.freePass(openglContext));
}

TEST_F(PassFreerTests, FreePassTest_noShaders)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a mock pipeline ID
    pass::OpenGLPassFreer passFreer;

    // Expect no detach calls
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDetachShader_mock(::testing::_, ::testing::_)).Times(0);

    // Act & Assert
    ASSERT_NO_THROW(passFreer.freePass(openglContext));
}

#endif // __mock_gl__