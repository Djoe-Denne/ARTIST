#ifdef __mock_gl__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <opengl/glFunctionMock.hpp>
#include <graphic/Api.hpp>
#include <graphic/opengl/context/AttributeContext.hpp>
#include <graphic/opengl/pipeline/component/attribute/Setter.hpp>
#include <common/exception/TraceableException.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::graphic::api;
namespace mock = cenpy::mock;
namespace context = cenpy::graphic::opengl::context;
namespace attribute = cenpy::graphic::opengl::pipeline::component::attribute;

using cenpy::test::utils::expectSpecificError;

class AttributeSetterTests : public ::testing::Test
{
protected:
    void TearDown() override
    {
        mock::opengl::glFunctionMock::reset();
    }
};

TEST_F(AttributeSetterTests, SetAttributeTest_CallBufferData)
{
    // Arrange
    std::shared_ptr<context::OpenGLAttributeContext> attribute = std::make_shared<context::OpenGLAttributeContext>();
    attribute->setBufferID(1);
    attribute->setGLUsage(GL_STATIC_DRAW);
    std::shared_ptr<float> attrValue = std::make_shared<float>(1.0f);
    attribute->setValue(attrValue);

    // Expected call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glBufferData_mock(GL_ARRAY_BUFFER, sizeof(attrValue.get()), attrValue.get(), GL_STATIC_DRAW))
        .Times(1);

    // Act
    attribute::OpenGLSetter<float>::on(attribute);
}

TEST_F(AttributeSetterTests, SetAttributeTest_CallVertexAttribPointer)
{
    // Arrange
    std::shared_ptr<context::OpenGLAttributeContext> attribute = std::make_shared<context::OpenGLAttributeContext>();
    attribute->setBufferID(1);
    attribute->setGLUsage(GL_STATIC_DRAW);
    attribute->setAttributeID(1);
    attribute->setGLSize(1);
    attribute->setGLType(GL_FLOAT);
    std::shared_ptr<float> attrValue = std::make_shared<float>(1.0f);
    attribute->setValue(attrValue);

    // Expected call
    EXPECT_CALL(*mock::opengl::glFunctionMock::instance(), glVertexAttribPointer_mock(1, 1, GL_FLOAT, GL_FALSE, sizeof(attrValue.get()), (void *)nullptr))
        .Times(1);

    // Act
    attribute::OpenGLSetter<float>::on(attribute);
}

TEST_F(AttributeSetterTests, SetAttributeTest_ThrowExceptionWhenContextIsNullptr)
{
    // Act & Assert
    expectSpecificError<std::runtime_error>([&]()
                                            { attribute::OpenGLSetter<float>::on(nullptr); },
                                            cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::ATTRIBUTE::SET::NON_OPENGL_CONTEXT"));
}

TEST_F(AttributeSetterTests, SetAttributeTest_ThrowExceptionWhenBufferIsNotSet)
{
    // Arrange
    std::shared_ptr<context::OpenGLAttributeContext> attribute = std::make_shared<context::OpenGLAttributeContext>();

    // Act & Assert
    expectSpecificError<std::runtime_error>([&]()
                                            { attribute::OpenGLSetter<float>::on(attribute); },
                                            cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::ATTRIBUTE::SET::BUFFER_ID_NOT_SET"));
}

#endif // __mock_gl__