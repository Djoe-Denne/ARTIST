#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/context/PipelineContext.hpp>
#include <graphic/pipeline/component/pipeline/Resetter.hpp>
#include <TestUtils.hpp>

using cenpy::graphic::opengl::context::OpenGLPipelineContext;
using cenpy::graphic::pipeline::opengl::component::pipeline::OpenGLPipelineResetter;
using cenpy::test::utils::expectSpecificError;

class ResetterTests : public ::testing::Test
{
};

TEST_F(ResetterTests, resetProgram_ValidContext)
{
    // Arrange
    auto context = std::make_shared<OpenGLPipelineContext>();
    context->setCurrentPass(42);
    OpenGLPipelineResetter resetter;

    // Act
    resetter.resetPipeline(context);

    // Assert
    ASSERT_EQ(context->getCurrentPass(), -1);
}

TEST_F(ResetterTests, resetProgram_NullContext)
{
    // Arrange
    OpenGLPipelineResetter resetter;

    // Act & Assert
    expectSpecificError([&resetter]()
                        { resetter.resetPipeline(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT")));
}
