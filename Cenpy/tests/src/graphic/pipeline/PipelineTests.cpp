
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <graphic/opengl/profile/Pipeline.hpp>
#include <graphic/opengl/validator/Validator.hpp>

#include <graphic/pipeline/Pipeline.hpp>
#include <graphic/pipeline/MockPass.hpp>
#include <graphic/opengl/context/MockPipelineContext.hpp>
#include <graphic/opengl/pipeline/component/pipeline/MockUser.hpp>
#include <graphic/opengl/pipeline/component/pipeline/MockResetter.hpp>
#include <graphic/MockApi.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock;

using mock::graphic::opengl::pipeline::component::pipeline::MockResetter;
using mock::graphic::opengl::pipeline::component::pipeline::MockUser;
using mock::graphic::pipeline::opengl::MockPass;

using cenpy::graphic::opengl::profile::Pipeline::Classic;
using cenpy::test::utils::expectSpecificError;

class PipelineTest : public ::testing::Test
{
};

TEST_F(PipelineTest, UseTest)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    pipeline::Pipeline<api::MockOpenGL, Classic> pipeline({mockPass1, mockPass2});

    // Expect calls
    EXPECT_CALL(*MockUser<Classic>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    pipeline.use(0); // Using first pass
}

TEST_F(PipelineTest, IteratePassesTest)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    pipeline::Pipeline<api::MockOpenGL, Classic> pipeline({mockPass1, mockPass2});

    // Expect calls
    EXPECT_CALL(*MockUser<Classic>::instance(), mockOn(::testing::_)).Times(2);

    // Act
    while (pipeline.hasNext())
    {
        pipeline.useNext();
    }
}

TEST_F(PipelineTest, ResetPipelineTest)
{
    // Arrange
    pipeline::Pipeline<api::MockOpenGL, Classic> pipeline({nullptr});

    // Expect calls
    EXPECT_CALL(*MockResetter<Classic>::instance(), mockOn(::testing::_)).Times(1);

    // Act
    pipeline.reset();
}

TEST_F(PipelineTest, GetContext)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    pipeline::Pipeline<api::MockOpenGL, Classic> pipeline({mockPass1, mockPass2});

    // Act
    auto context = pipeline.getContext();

    // Assert
    ASSERT_NE(context, nullptr);
}