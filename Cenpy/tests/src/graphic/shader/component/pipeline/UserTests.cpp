#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <graphic/context/PipelineContext.hpp>
#include <graphic/pipeline/MockPass.hpp>
#include <graphic/pipeline/component/pipeline/User.hpp>
#include <graphic/Api.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace api = cenpy::graphic::api;

using cenpy::graphic::pipeline::opengl::component::pipeline::OpenGLPipelineUser;
using cenpy::mock::graphic::pipeline::opengl::MockPass;
using cenpy::test::utils::expectSpecificError;

class UserTests : public ::testing::Test
{
};

TEST_F(UserTests, useProgram_ValidContext)
{
    // Arrange
    auto context = std::make_shared<context::OpenGLPipelineContext>();
    context->setCurrentPass(0);
    auto pass = std::make_shared<MockPass<api::OpenGL>>();
    context->addPass(pass);
    OpenGLPipelineUser user;

    // Expect
    EXPECT_CALL(*pass, use()).Times(1);

    // Act
    user.usePipeline(context);
}

TEST_F(UserTests, useProgram_NullContext)
{
    // Arrange
    OpenGLPipelineUser user;

    // Act & Assert
    expectSpecificError([&user]()
                        { user.usePipeline(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::NON_VALID_CONTEXT")));
}