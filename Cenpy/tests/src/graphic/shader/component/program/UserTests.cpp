#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/context/ProgramContext.hpp>
#include <graphic/shader/MockPass.hpp>
#include <graphic/shader/component/program/User.hpp>
#include <graphic/Api.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace api = cenpy::graphic::api;

using cenpy::graphic::shader::opengl::component::program::OpenGLProgramUser;
using cenpy::mock::graphic::shader::opengl::MockPass;
using cenpy::test::utils::expectSpecificError;

class UserTests : public ::testing::Test
{
};

TEST_F(UserTests, useProgram_ValidContext)
{
    // Arrange
    auto context = std::make_shared<context::OpenGLProgramContext>();
    context->setCurrentPass(0);
    auto pass = std::make_shared<MockPass<api::OpenGL>>();
    context->addPass(pass);
    OpenGLProgramUser user;

    // Expect
    EXPECT_CALL(*pass, use()).Times(1);

    // Act
    user.useProgram(context);
}

TEST_F(UserTests, useProgram_NullContext)
{
    // Arrange
    OpenGLProgramUser user;

    // Act & Assert
    expectSpecificError([&user]()
                        { user.useProgram(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT")));
}