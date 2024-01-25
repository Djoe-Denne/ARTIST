#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/AttributeContext.hpp>
#include <graphic/opengl/pipeline/component/attribute/Unbinder.hpp>
#include <common/exception/TraceableException.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::graphic::api;
namespace mock = cenpy::mock;
namespace context = cenpy::graphic::opengl::context;
namespace attribute = cenpy::graphic::opengl::pipeline::component::attribute;
using cenpy::graphic::opengl::profile::Attribute::Classic;
using cenpy::test::utils::expectSpecificError;

class AttributeUnbinderTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(AttributeUnbinderTests, BindAttributeTest_unbindBuffer)
{
    // Arrange
    auto attributeContext = std::make_shared<api::OpenGL::AttributeContext>();
    attributeContext->setBufferID(42);

    auto unbinder = std::make_shared<attribute::OpenGLUnbinder<Classic>>();

    // Expected call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glBindBuffer_mock(GL_ARRAY_BUFFER, 0))
        .Times(1);

    // Act
    ASSERT_NO_THROW(unbinder->on(attributeContext));
}

TEST_F(AttributeUnbinderTests, BindAttributeTest_nullContext)
{
    // Arrange
    auto unbinder = std::make_shared<attribute::OpenGLUnbinder<Classic>>();

    // Act & Assert
    expectSpecificError([&unbinder]()
                        { unbinder->on(nullptr); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::ATTRIBUTE::UNBIND::NON_OPENGL_CONTEXT"));
}

TEST_F(AttributeUnbinderTests, BindAttributeTest_defaultBindID)
{
    // Arrange
    auto attributeContext = std::make_shared<api::OpenGL::AttributeContext>();
    attributeContext->setBufferID(0);

    auto unbinder = std::make_shared<attribute::OpenGLUnbinder<Classic>>();

    // Expected call
    expectSpecificError([&unbinder, &attributeContext]()
                        { unbinder->on(attributeContext); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::ATTRIBUTE::UNBIND::BUFFER_ID_NOT_SET"));
}

#endif // __mock_gl__