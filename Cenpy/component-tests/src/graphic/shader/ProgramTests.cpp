#include <memory>
#include <gtest/gtest.h>
#include <graphic/pipeline/Pipeline.hpp>
#include <graphic/Api.hpp>
#include <graphic/context/PipelineContext.hpp>
#include <graphic/context/PassContext.hpp>
#include <OpenGLComponentTests.hpp>

namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;

class PipelineTest : public OpenGLComponentTest
{
protected:
    std::shared_ptr<pipeline::Pass<api::OpenGL>> pass1;
    std::shared_ptr<pipeline::Pass<api::OpenGL>> pass2;

    void SetUp() override
    {
        OpenGLComponentTest::SetUp();
        // Initialize Passes with valid shaders
        auto vertexShader = std::make_shared<pipeline::Shader<api::OpenGL>>("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);
        auto fragmentShader = std::make_shared<pipeline::Shader<api::OpenGL>>("test-datas/shaders/fragment/good/minimal.frag", context::ShaderType::FRAGMENT);
        pass1 = std::shared_ptr<pipeline::Pass<api::OpenGL>>(new pipeline::Pass<api::OpenGL>({vertexShader, fragmentShader}));
        pass2 = std::shared_ptr<pipeline::Pass<api::OpenGL>>(new pipeline::Pass<api::OpenGL>({vertexShader, fragmentShader}));
    }
};

TEST_F(PipelineTest, PipelineCreationTest)
{
    ASSERT_NO_THROW(pipeline::Pipeline pipeline({pass1, pass2}));
}

TEST_F(PipelineTest, UsePassTest)
{
    pipeline::Pipeline pipeline({pass1, pass2});

    // Test using the first pass
    ASSERT_NO_THROW(pipeline.use(0));
    // Add checks if there are specific observable effects of using a pass

    // Test using the second pass
    ASSERT_NO_THROW(pipeline.use(1));
    // Add checks for the second pass
}

TEST_F(PipelineTest, UseNextPassTest)
{
    pipeline::Pipeline pipeline({pass1, pass2});

    // Use the first pass and then the next
    ASSERT_TRUE(pipeline.hasNext());
    ASSERT_TRUE(pipeline.useNext());
    ASSERT_FALSE(pipeline.useNext());
}

TEST_F(PipelineTest, ResetPipelineTest)
{
    pipeline::Pipeline pipeline({pass1, pass2});

    pipeline.use(0);
    ASSERT_NO_THROW(pipeline.reset());
    // Add checks to ensure the pipeline is reset to its initial state
}

TEST_F(PipelineTest, PassesCountTest)
{
    pipeline::Pipeline pipeline({pass1, pass2});

    ASSERT_EQ(pipeline.getPassesCount(), 2);
}

// Additional tests can be added based on other functionalities of the Pipeline class
