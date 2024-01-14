#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/context/PassContext.hpp>
#include <graphic/pipeline/component/pass/User.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::pipeline::opengl::component::pass;
namespace mock = cenpy::mock;
using cenpy::test::utils::expectSpecificError;

class UserTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(UserTests, UsePass_ValidContext)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a valid pipeline ID
    pass::OpenGLPassUser passUser;

    // Expect call to glUsePipeline with the correct pipeline ID
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glUseProgram_mock(1)).Times(1);

    // Act
    ASSERT_NO_THROW(passUser.usePass(openglContext));

    // Additional validations can be performed here if necessary
}

TEST_F(UserTests, UsePass_NullContext)
{
    // Arrange
    pass::OpenGLPassUser passUser;

    // Act & Assert
    expectSpecificError([&passUser]()
                        { passUser.usePass(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT"));
}

#endif // __mock_gl__