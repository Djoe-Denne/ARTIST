#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <graphic/opengl/pipeline/component/attribute/Setter.hpp>
#include <graphic/opengl/pipeline/component/attribute/Binder.hpp>
#include <graphic/opengl/pipeline/component/attribute/Unbinder.hpp>

#include <graphic/opengl/validator/Validator.hpp>
#include <graphic/opengl/profile/Pass.hpp>

#include <graphic/opengl/pipeline/component/pass/AttributeReader.hpp>
#include <TestUtils.hpp>

namespace context = cenpy::graphic::opengl::context;
namespace pass = cenpy::graphic::opengl::pipeline::component::pass;
namespace mock = cenpy::mock;
using cenpy::graphic::opengl::profile::Pass::Classic;
using cenpy::test::utils::expectSpecificError;

class AttributeReaderTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(AttributeReaderTests, ReadAttributes_CallGetProgramiv)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a valid pipeline ID

    // Mock the OpenGL calls to simulate attributes
    GLint numAttributes = 0; // For example, 2 attributes
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, GL_ACTIVE_ATTRIBUTES, ::testing::_))
        .WillOnce(::testing::SetArgPointee<2>(numAttributes));

    // Act
    ASSERT_NO_THROW(pass::OpenGLPassAttributeReader<Classic>::on(openglContext));
}

TEST_F(AttributeReaderTests, ReadAttributes_CallGetActiveAttribAndGetAttribLocation)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>();
    openglContext->setPassID(1); // Set a valid pipeline ID

    // Mock the OpenGL calls to simulate attributes
    GLint numAttributes = 1; // For example, 2 attributes
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetProgramiv_mock(1, GL_ACTIVE_ATTRIBUTES, ::testing::_))
        .WillOnce(::testing::SetArgPointee<2>(numAttributes));

    // Mock calls to glGetActiveAttribute and glGetAttributeLocation for each attribute
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetActiveAttrib_mock(1, 0, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .Times(1);
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGetAttribLocation_mock(1, ::testing::_))
        .Times(1);

    // Act
    ASSERT_NO_THROW(pass::OpenGLPassAttributeReader<Classic>::on(openglContext));

    // Assert
    // Optionally check if the attributes are correctly added to the context
    ASSERT_EQ(openglContext->getAttributes().size(), 1);
    ASSERT_TRUE(openglContext->getAttributes().contains(mock::opengl::glFunctionMock::ATTRIBUTE_NAME));
}

TEST_F(AttributeReaderTests, ReadAttributes_NullContext)
{
    // Arrange

    // Act & Assert
    expectSpecificError([]()
                        { pass::OpenGLPassAttributeReader<Classic>::on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::PASS::NON_OPENGL_CONTEXT"));
}

TEST_F(AttributeReaderTests, ReadAttributes_InvalidPassID)
{
    // Arrange
    auto openglContext = std::make_shared<context::OpenGLPassContext>(); // No pipeline ID set

    // Act & Assert
    expectSpecificError([&openglContext]()
                        { pass::OpenGLPassAttributeReader<Classic>::on(openglContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::PASS::INVALID_PROGRAM_ID"));
}

#endif // __mock_gl__