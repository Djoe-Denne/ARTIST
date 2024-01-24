#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/opengl/context/MockUniformContext.hpp>
#include <graphic/opengl/pipeline/component/uniform/MockSetter.hpp>
#include <graphic/opengl/validator/Validator.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/pipeline/component/pass/User.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::opengl::pipeline::component::pass;
namespace mock = cenpy::mock;
using cenpy::graphic::opengl::profile::Pass::Classic;
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

    // Expect call to glUsePipeline with the correct pipeline ID
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glUseProgram_mock(1)).Times(1);

    // Act
    ASSERT_NO_THROW(pass::OpenGLPassUser<Classic>::on(openglContext));

    // Additional validations can be performed here if necessary
}

TEST_F(UserTests, UsePass_NullContext)
{
    // Arrange

    // Act & Assert
    expectSpecificError([]()
                        { pass::OpenGLPassUser<Classic>::on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::NON_OPENGL_CONTEXT"));
}

#endif // __mock_gl__