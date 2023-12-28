#include <gtest/gtest.h>
#include <graphic/shader/Pass.hpp>
#include <OpenGLComponentTests.hpp>

namespace shader = cenpy::graphic::shader;

class PassTest : public OpenGLComponentTest
{
protected:
    std::shared_ptr<shader::opengl::Shader> vertexShader;
    std::shared_ptr<shader::opengl::Shader> fragmentShader;

    void SetUp() override
    {
        OpenGLComponentTest::SetUp();
        vertexShader = std::make_shared<shader::opengl::Shader>("test-datas/shaders/vertex/good/minimal.vert", shader::ShaderType::VERTEX);
        fragmentShader = std::make_shared<shader::opengl::Shader>("test-datas/shaders/fragment/good/minimal.frag", shader::ShaderType::FRAGMENT);
    }
};

TEST_F(PassTest, PassCreationTest)
{
    ASSERT_NO_THROW(shader::opengl::Pass(vertexShader, fragmentShader));
}

TEST_F(PassTest, UniformManagementTest)
{
    shader::opengl::Pass pass(vertexShader, fragmentShader);
    int testValue = 5;

    ASSERT_NO_THROW(pass.withUniform("testUniform", testValue));

    auto uniforms = pass.getUniforms();
    ASSERT_TRUE(uniforms.contains("testUniform"));
    auto uniform = uniforms.at("testUniform");
    ASSERT_NE(uniform, nullptr);
    ASSERT_EQ(uniform->get<int>(), testValue);
}

TEST_F(PassTest, InvalidUniformTest)
{
    shader::opengl::Pass pass(vertexShader, fragmentShader);

    EXPECT_THROW(pass.withUniform("nonExistentUniform", 5), cenpy::common::exception::TraceableException<std::runtime_error>);
}

TEST_F(PassTest, ShaderAttachmentTest)
{
    shader::opengl::Pass pass(vertexShader, fragmentShader);

    // Since attachShaders is protected, we assume its correctness through the absence of exceptions during Pass creation
    ASSERT_NO_THROW(shader::opengl::Pass(vertexShader, fragmentShader));
}

TEST_F(PassTest, UniformReadingTest)
{
    shader::opengl::Pass pass(vertexShader, fragmentShader);

    auto uniforms = pass.getUniforms();
    // Assuming the shaders have at least one uniform
    ASSERT_FALSE(uniforms.empty());
    // Further checks can be added here based on specific uniforms expected in the shaders
}

TEST_F(PassTest, LoadPassTest)
{
    ASSERT_NO_THROW(shader::opengl::Pass pass(vertexShader, fragmentShader));
    // Additional checks on the state of Pass after loading can be added, if possible
}

TEST_F(PassTest, FreeResourcesTest)
{
    // This test assumes that freeing resources does not cause any observable side effects that can be checked.
    // As such, we are limited to testing for the absence of exceptions.
    auto pass = new shader::opengl::Pass(vertexShader, fragmentShader);

    ASSERT_NO_THROW(delete pass);
}
