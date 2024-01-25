#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/pipeline/component/uniform/MockSetter.hpp>

#include <graphic/opengl/validator/Validator.hpp>
#include <graphic/opengl/profile/Pass.hpp>

#include <graphic/opengl/pipeline/component/pass/UniformReader.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::opengl::pipeline::component::pass;
namespace mock = cenpy::mock;
using cenpy::graphic::opengl::profile::Pass::Classic;
using cenpy::test::utils::expectSpecificError;

class UniformReaderTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(UniformReaderTests, ReadUniforms_ValidContext)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a valid pipeline ID

    // Mock the OpenGL calls to simulate uniforms
    GLint numUniforms = 1; // For example, 2 uniforms
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, GL_ACTIVE_UNIFORMS, ::testing::_))
        .WillOnce(::testing::SetArgPointee<2>(numUniforms));

    // Mock calls to glGetActiveUniform and glGetUniformLocation for each uniform
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetActiveUniform_mock(1, 0, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetUniformLocation_mock(1, ::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(pass::OpenGLPassUniformReader<Classic>::on(openglContext));

    // Assert
    // Optionally check if the uniforms are correctly added to the context
    ASSERT_EQ(openglContext->getUniforms().size(), 1);
    ASSERT_TRUE(openglContext->getUniforms().contains(mock::opengl::glFunctionMock::UNIFORM_NAME));
}

TEST_F(UniformReaderTests, ReadUniforms_NullContext)
{
    // Arrange

    // Act & Assert
    expectSpecificError([]()
                        { pass::OpenGLPassUniformReader<Classic>::on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::PASS::NON_OPENGL_CONTEXT"));
}

TEST_F(UniformReaderTests, ReadUniforms_InvalidPassID)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>(); // No pipeline ID set

    // Act & Assert
    expectSpecificError([&openglContext]()
                        { pass::OpenGLPassUniformReader<Classic>::on(openglContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::PASS::INVALID_PROGRAM_ID"));
}

#endif // __mock_gl__