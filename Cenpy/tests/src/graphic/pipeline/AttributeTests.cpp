#include <any>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <graphic/opengl/profile/Attribute.hpp>
#include <graphic/opengl/validator/Validator.hpp>
#include <graphic/pipeline/Attribute.hpp>
#include <graphic/opengl/context/MockAttributeContext.hpp>
#include <graphic/opengl/pipeline/component/attribute/MockSetter.hpp>
#include <graphic/opengl/pipeline/component/attribute/MockBinder.hpp>
#include <graphic/opengl/pipeline/component/attribute/MockUnbinder.hpp>
#include <graphic/MockApi.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::opengl::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock::graphic::opengl::pipeline::component::attribute;

using cenpy::graphic::opengl::profile::Attribute::Classic;

class AttributeTest : public ::testing::Test
{
public:
    void TearDown() override
    {
    }
};

TEST_F(AttributeTest, BindTest)
{
    // Arrange
    auto attributeContext = std::make_shared<api::MockOpenGL::AttributeContext>();

    pipeline::Attribute<api::MockOpenGL, Classic> attribute(attributeContext);

    // Expect calls
    EXPECT_CALL(*mock::MockBinder<Classic>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(attribute.bind());
}

TEST_F(AttributeTest, UnbindTest)
{
    // Arrange
    auto attributeContext = std::make_shared<api::MockOpenGL::AttributeContext>();

    pipeline::Attribute<api::MockOpenGL, Classic> attribute(attributeContext);

    // Expect calls
    EXPECT_CALL(*mock::MockUnbinder<Classic>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(attribute.unbind());
}

TEST_F(AttributeTest, SetTest)
{
    // Arrange
    auto attributeContext = std::make_shared<api::MockOpenGL::AttributeContext>();

    pipeline::Attribute<api::MockOpenGL, Classic> attribute(attributeContext);

    // Expect calls
    EXPECT_CALL(*mock::MockSetter<int>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    ASSERT_NO_THROW(attribute.set(std::make_shared<int>(1)));
}

TEST_F(AttributeTest, GetContextTest)
{
    // Arrange
    auto attributeContext = std::make_shared<api::MockOpenGL::AttributeContext>();

    pipeline::Attribute<api::MockOpenGL, Classic> attribute(attributeContext);

    // Act
    ASSERT_EQ(attributeContext, attribute.getContext());
}