#include <gtest/gtest.h>
#include <graphic/shader/Pass.hpp>
#include <graphic/Api.hpp>
#include <graphic/context/PassContext.hpp>
#include <OpenGLComponentTests.hpp>

namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::context;
namespace shader = cenpy::graphic::shader;

class PassTest : public OpenGLComponentTest
{
protected:
    std::shared_ptr<shader::Shader<api::OpenGL>> vertexShader;
    std::shared_ptr<shader::Shader<api::OpenGL>> fragmentShader;

    void SetUp() override
    {
        OpenGLComponentTest::SetUp();
        vertexShader = std::make_shared<shader::Shader<api::OpenGL>>("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);
        fragmentShader = std::make_shared<shader::Shader<api::OpenGL>>("test-datas/shaders/fragment/good/minimal.frag", context::ShaderType::FRAGMENT);
    }
};

TEST_F(PassTest, PassCreationTest)
{
    ASSERT_NO_THROW(shader::Pass<api::OpenGL>({vertexShader, fragmentShader}));
}

TEST_F(PassTest, UniformManagementTest)
{
    shader::Pass<api::OpenGL> pass({vertexShader, fragmentShader});
    pass.load();

    float testValue = 5.0f;

    ASSERT_NO_THROW(pass.withUniform("testUniform", testValue));

    auto uniforms = pass.getUniforms();
    ASSERT_TRUE(uniforms.contains("testUniform"));
    auto uniform = uniforms.at("testUniform");
    ASSERT_NE(uniform, nullptr);
    ASSERT_EQ(uniform->get<float>(), testValue);
}

TEST_F(PassTest, InvalidUniformTest)
{
    shader::Pass<api::OpenGL> pass({vertexShader, fragmentShader});

    EXPECT_THROW(pass.withUniform("nonExistentUniform", 5), cenpy::common::exception::TraceableException<std::runtime_error>);
}

TEST_F(PassTest, ShaderAttachmentTest)
{
    shader::Pass<api::OpenGL> pass({vertexShader, fragmentShader});

    // Since attachShaders is protected, we assume its correctness through the absence of exceptions during Pass creation
    ASSERT_NO_THROW(shader::Pass<api::OpenGL>({vertexShader, fragmentShader}));
}

TEST_F(PassTest, UniformReadingTest)
{
    shader::Pass<api::OpenGL> pass({vertexShader, fragmentShader});
    pass.load();
    const auto &uniforms = pass.getUniforms();
    // Assuming the shaders have at least one uniform
    ASSERT_FALSE(uniforms.empty());
    // Further checks can be added here based on specific uniforms expected in the shaders
}

TEST_F(PassTest, LoadPassTest)
{
    ASSERT_NO_THROW(shader::Pass<api::OpenGL> pass({vertexShader, fragmentShader}));
    // Additional checks on the state of Pass after loading can be added, if possible
}

TEST_F(PassTest, FreeResourcesTest)
{
    // This test assumes that freeing resources does not cause any observable side effects that can be checked.
    // As such, we are limited to testing for the absence of exceptions.
    auto pass = new shader::Pass<api::OpenGL>({vertexShader, fragmentShader});

    ASSERT_NO_THROW(delete pass);
}
