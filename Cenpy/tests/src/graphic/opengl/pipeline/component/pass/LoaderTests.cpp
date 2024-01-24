#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/MockApi.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/pipeline/component/pass/MockShaderAttacher.hpp>
#include <graphic/opengl/pipeline/component/pass/Loader.hpp>
#include <TestUtils.hpp>

namespace mock = cenpy::mock;
namespace mock_component = cenpy::mock::graphic::opengl::pipeline::component::pass;
namespace context = cenpy::graphic::opengl::context;
namespace api = cenpy::graphic::api;
namespace pass = cenpy::graphic::opengl::pipeline::component::pass;

using cenpy::graphic::opengl::profile::Pass::Classic;
using cenpy::test::utils::expectSpecificError;

class LoaderTests : public ::testing::Test
{
public:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(LoaderTests, LoadPassTest_validContext)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();

    // Act
    ASSERT_NO_THROW(pass::OpenGLLoader<Classic>::on(openglContext));

    // Assert
    ASSERT_EQ(openglContext->getPassID(), 1);
}

TEST_F(LoaderTests, LoadPassTest_createPipeline)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();

    // Expect calls for valid context
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateProgram_mock()).Times(1);

    // Act
    ASSERT_NO_THROW(pass::OpenGLLoader<Classic>::on(openglContext));
}

TEST_F(LoaderTests, LoadPassTest_linkPipeline)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();

    // Expect calls for valid context
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glLinkProgram_mock(1)).Times(1);

    // Act
    ASSERT_NO_THROW(pass::OpenGLLoader<Classic>::on(openglContext));
}

TEST_F(LoaderTests, LoadPassTest_nullContext)
{
    // Arrange
    // Act & Assert
    expectSpecificError([]()
                        { pass::OpenGLLoader<Classic>::on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM::NON_OPENGL_CONTEXT")));
}

TEST_F(LoaderTests, LoadPassTest_pipelineCreationFailed)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();

    // Expect calls for pipeline creation failure
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glCreateProgram_mock())
        .WillOnce(::testing::Return(0));

    // Act & Assert
    expectSpecificError([&openglContext]()
                        { pass::OpenGLLoader<Classic>::on(openglContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM_CREATION_FAILED\nFailed to create shader pipeline.")));
}

TEST_F(LoaderTests, LoadPassTest_linkFailed)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();

    // Set mock behavior for link failure

    // Expect calls for link failure
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, GL_LINK_STATUS, ::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](GLuint program, GLenum pname, GLint *params)
                                    { *params = GL_FALSE; }));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, GL_INFO_LOG_LENGTH, ::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](GLuint program, GLenum pname, GLint *params)
                                    { *params = 300; }));
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramInfoLog_mock(1, 300, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glDeleteProgram_mock(1)).Times(1);

    // Act & Assert
    expectSpecificError([&openglContext]()
                        { pass::OpenGLLoader<Classic>::on(openglContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::SHADER::PROGRAM::LINK_FAILED")));
}

TEST_F(LoaderTests, LoadPassTest_linkSuccess)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();

    // Set mock behavior for link success

    // Expect calls for link success
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, GL_LINK_STATUS, ::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](GLuint program, GLenum pname, GLint *params)
                                    { *params = GL_TRUE; }));

    // Act & Assert
    ASSERT_NO_THROW(pass::OpenGLLoader<Classic>::on(openglContext));
}

#endif // __mock_gl__
