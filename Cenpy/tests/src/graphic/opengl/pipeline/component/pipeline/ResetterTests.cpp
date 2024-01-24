#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/opengl/context/PipelineContext.hpp>
#include <graphic/opengl/profile/Pipeline.hpp>
#include <graphic/opengl/pipeline/component/pipeline/Resetter.hpp>
#include <TestUtils.hpp>

using cenpy::graphic::opengl::context::OpenGLPipelineContext;
using cenpy::graphic::opengl::pipeline::component::pipeline::OpenGLPipelineResetter;
using cenpy::graphic::opengl::profile::Pipeline::Classic;
using cenpy::test::utils::expectSpecificError;

class ResetterTests : public ::testing::Test
{
};

TEST_F(ResetterTests, resetProgram_ValidContext)
{
    // Arrange
    auto context = std::make_shared<OpenGLPipelineContext>();
    context->setCurrentPass(42);

    // Act
    OpenGLPipelineResetter<Classic>::on(context);

    // Assert
    ASSERT_EQ(context->getCurrentPass(), -1);
}

TEST_F(ResetterTests, resetProgram_NullContext)
{
    // Arrange

    // Act & Assert
    expectSpecificError([]()
                        { OpenGLPipelineResetter<Classic>::on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT")));
}
