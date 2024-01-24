#include <gtest/gtest.h>
#include <graphic/pipeline/Pass.hpp>

#include <graphic/opengl/profile/Pass.hpp>
#include <graphic/opengl/profile/Shader.hpp>
#include <graphic/opengl/validator/Validator.hpp>
#include <graphic/opengl/pipeline/component/attribute/Binder.hpp>
#include <graphic/opengl/pipeline/component/attribute/Setter.hpp>
#include <graphic/opengl/pipeline/component/attribute/Unbinder.hpp>
#include <graphic/opengl/pipeline/component/uniform/Setter.hpp>
#include <graphic/opengl/pipeline/component/shader/Freer.hpp>
#include <graphic/opengl/pipeline/component/shader/Loader.hpp>
#include <graphic/opengl/pipeline/component/shader/Reader.hpp>
#include <graphic/opengl/pipeline/component/pass/ShaderAttacher.hpp>
#include <graphic/opengl/pipeline/component/pass/UniformReader.hpp>
#include <graphic/opengl/pipeline/component/pass/AttributeReader.hpp>
#include <graphic/opengl/pipeline/component/pass/Loader.hpp>
#include <graphic/opengl/pipeline/component/pass/User.hpp>
#include <graphic/opengl/pipeline/component/pass/Freer.hpp>

#include <graphic/Api.hpp>
#include <graphic/opengl/context/PassContext.hpp>
#include <OpenGLComponentTests.hpp>

namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
namespace profile = cenpy::graphic::opengl::profile;

class PassTest : public OpenGLComponentTest
{
protected:
    std::shared_ptr<pipeline::IShader<api::OpenGL>> vertexShader;
    std::shared_ptr<pipeline::IShader<api::OpenGL>> fragmentShader;

    void SetUp() override
    {
        OpenGLComponentTest::SetUp();
        vertexShader = std::make_shared<pipeline::Shader<api::OpenGL, profile::Shader::Classic>>("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);
        fragmentShader = std::make_shared<pipeline::Shader<api::OpenGL, profile::Shader::Classic>>("test-datas/shaders/fragment/good/minimal.frag", context::ShaderType::FRAGMENT);
    }
};

TEST_F(PassTest, PassCreationTest)
{
    ASSERT_NO_THROW((pipeline::Pass<api::OpenGL, profile::Pass::Classic>({vertexShader, fragmentShader})));
}

TEST_F(PassTest, UniformManagementTest)
{
    pipeline::Pass<api::OpenGL, profile::Pass::Classic> pass({vertexShader, fragmentShader});
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
    pipeline::Pass<api::OpenGL, profile::Pass::Classic> pass({vertexShader, fragmentShader});

    EXPECT_THROW(pass.withUniform("nonExistentUniform", 5), cenpy::common::exception::TraceableException<std::runtime_error>);
}

TEST_F(PassTest, ShaderAttachmentTest)
{
    pipeline::Pass<api::OpenGL, profile::Pass::Classic> pass({vertexShader, fragmentShader});

    // Since on is protected, we assume its correctness through the absence of exceptions during Pass creation
    ASSERT_NO_THROW((pipeline::Pass<api::OpenGL, profile::Pass::Classic>({vertexShader, fragmentShader})));
}

TEST_F(PassTest, UniformReadingTest)
{
    pipeline::Pass<api::OpenGL, profile::Pass::Classic> pass({vertexShader, fragmentShader});
    pass.load();
    const auto &uniforms = pass.getUniforms();
    // Assuming the shaders have at least one uniform
    ASSERT_FALSE(uniforms.empty());
    // Further checks can be added here based on specific uniforms expected in the shaders
}

TEST_F(PassTest, FreeResourcesTest)
{
    // This test assumes that freeing resources does not cause any observable side effects that can be checked.
    // As such, we are limited to testing for the absence of exceptions.
    auto pass = new pipeline::Pass<api::OpenGL, profile::Pass::Classic>({vertexShader, fragmentShader});

    ASSERT_NO_THROW(delete pass);
}
