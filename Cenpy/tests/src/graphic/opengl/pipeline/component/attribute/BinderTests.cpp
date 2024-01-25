#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/AttributeContext.hpp>
#include <graphic/opengl/pipeline/component/attribute/Binder.hpp>
#include <common/exception/TraceableException.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::graphic::api;
namespace mock = cenpy::mock;
namespace context = cenpy::graphic::opengl::context;
namespace attribute = cenpy::graphic::opengl::pipeline::component::attribute;
using cenpy::graphic::opengl::profile::Attribute::Classic;
using cenpy::test::utils::expectSpecificError;

class AttributeBinderTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(AttributeBinderTests, BindAttributeTest_createBuffer)
{
    // Arrange
    auto attributeContext = std::make_shared<api::OpenGL::AttributeContext>();
    attributeContext->setBufferID(0);
    attributeContext->setGLType(GL_FLOAT);
    attributeContext->setGLSize(1);

    auto binder = std::make_shared<attribute::OpenGLBinder<Classic>>();

    // Expected call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glGenBuffers_mock(1, ::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](GLsizei, GLuint *buffer)
                                    { *buffer = 42; }));

    // Act
    ASSERT_NO_THROW(binder->on(attributeContext));

    // Assert
    ASSERT_EQ(attributeContext->getBufferID(), 42);
}

TEST_F(AttributeBinderTests, BindAttributeTest_bindBuffer)
{
    // Arrange
    auto attributeContext = std::make_shared<api::OpenGL::AttributeContext>();
    attributeContext->setBufferID(42);
    attributeContext->setGLType(GL_FLOAT);
    attributeContext->setGLSize(1);

    auto binder = std::make_shared<attribute::OpenGLBinder<Classic>>();

    // Expected call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glBindBuffer_mock(GL_ARRAY_BUFFER, 42))
        .Times(1);

    // Act
    ASSERT_NO_THROW(binder->on(attributeContext));

    // Assert
    ASSERT_EQ(attributeContext->getBufferID(), 42);
}

TEST_F(AttributeBinderTests, BindAttributeTest_invalidContext)
{
    // Arrange
    auto binder = std::make_shared<attribute::OpenGLBinder<Classic>>();

    // Act & Assert
    expectSpecificError([&binder]()
                        { binder->on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>(std::format("ERROR::ATTRIBUTE::SET::NON_OPENGL_CONTEXT")));
}

#endif // __mock_gl__