#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/context/ProgramContext.hpp>
#include <graphic/shader/component/program/Resetter.hpp>
#include <TestUtils.hpp>

using cenpy::graphic::opengl::context::OpenGLProgramContext;
using cenpy::graphic::shader::opengl::component::program::OpenGLProgramResetter;
using cenpy::test::utils::expectSpecificError;

class ResetterTests : public ::testing::Test
{
};

TEST_F(ResetterTests, resetProgram_ValidContext)
{
    // Arrange
    auto context = std::make_shared<OpenGLProgramContext>();
    context->setCurrentPass(42);
    OpenGLProgramResetter resetter;

    // Act
    resetter.resetProgram(context);

    // Assert
    ASSERT_EQ(context->getCurrentPass(), -1);
}

TEST_F(ResetterTests, resetProgram_NullContext)
{
    // Arrange
    OpenGLProgramResetter resetter;

    // Act & Assert
    expectSpecificError([&resetter]()
                        { resetter.resetProgram(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT")));
}
