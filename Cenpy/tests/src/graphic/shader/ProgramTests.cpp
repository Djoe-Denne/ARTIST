
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <graphic/pipeline/Pipeline.hpp>
#include <graphic/pipeline/Pass.hpp>
#include <graphic/pipeline/MockPass.hpp>
#include <graphic/pipeline/component/pipeline/MockUser.hpp>
#include <graphic/pipeline/component/pipeline/MockResetter.hpp>
#include <graphic/context/MockPipelineContext.hpp>
#include <graphic/MockApi.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::mock::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace mock = cenpy::mock;

using mock::graphic::pipeline::opengl::MockPass;
using mock::graphic::pipeline::opengl::component::pipeline::MockResetter;
using mock::graphic::pipeline::opengl::component::pipeline::MockUser;

using cenpy::test::utils::expectSpecificError;

class PipelineTest : public ::testing::Test
{
};

class MockedPipeline : public pipeline::Pipeline<api::MockOpenGL>
{
public:
    using pipeline::Pipeline<api::MockOpenGL>::Pipeline;

    std::shared_ptr<MockResetter<api::MockOpenGL>> getResetter() const override
    {
        return pipeline::Pipeline<api::MockOpenGL>::getResetter();
    }

    std::shared_ptr<MockUser<api::MockOpenGL>> getUser() const override
    {
        return pipeline::Pipeline<api::MockOpenGL>::getUser();
    }

    friend class PipelineTest;
};

TEST_F(PipelineTest, UseTest)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    MockedPipeline pipeline({mockPass1, mockPass2});

    // Expect calls
    EXPECT_CALL(*pipeline.getUser(), usePipeline(::testing::_)).Times(1);

    // Act
    pipeline.use(0); // Using first pass
}

TEST_F(PipelineTest, IteratePassesTest)
{
    // Arrange
    auto mockPass1 = std::make_shared<MockPass<api::MockOpenGL>>();
    auto mockPass2 = std::make_shared<MockPass<api::MockOpenGL>>();
    MockedPipeline pipeline({mockPass1, mockPass2});

    // Expect calls
    EXPECT_CALL(*pipeline.getUser(), usePipeline(::testing::_)).Times(2);

    // Act
    while (pipeline.hasNext())
    {
        pipeline.useNext();
    }
}

TEST_F(PipelineTest, ResetPipelineTest)
{
    // Arrange
    MockedPipeline pipeline({nullptr});

    // Expect calls
    EXPECT_CALL(*pipeline.getResetter(), resetPipeline(::testing::_)).Times(1);

    // Act
    pipeline.reset();
}