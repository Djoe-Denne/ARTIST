#include <string>
#include <graphic/pipeline/Shader.hpp>
#include <OpenGLComponentTests.hpp>
#include <graphic/Api.hpp>
#include <OpenGLComponentTests.hpp>
#include <TestUtils.hpp>

namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::context;
namespace pipeline = cenpy::graphic::pipeline;
using cenpy::test::utils::expectSpecificError;

class ShaderTest : public OpenGLComponentTest
{
};

TEST_F(ShaderTest, CreateShaderVert)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getContext()->getShaderID(), 1);
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::VERTEX);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadVert)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/vertex/bad/minimal.vert", context::ShaderType::VERTEX);

    // Act
    expectSpecificError([&shader]()
                        { shader.load(); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::COMPILATION_FAILED"));
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::VERTEX);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderFrag)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/fragment/good/minimal.frag", context::ShaderType::FRAGMENT);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getContext()->getShaderID(), 1);
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::FRAGMENT);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadFrag)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/fragment/bad/minimal.frag", context::ShaderType::FRAGMENT);

    // Act
    expectSpecificError([&shader]()
                        { shader.load(); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::COMPILATION_FAILED"));
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::FRAGMENT);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderGeom)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/geometry/good/minimal.geom", context::ShaderType::GEOMETRY);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getContext()->getShaderID(), 1);
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::GEOMETRY);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadGeom)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/geometry/bad/minimal.geom", context::ShaderType::GEOMETRY);

    // Act
    expectSpecificError([&shader]()
                        { shader.load(); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::COMPILATION_FAILED"));
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::GEOMETRY);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderTesselaionControl)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/tesselaion_control/good/minimal.tesc", context::ShaderType::TESS_CONTROL);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getContext()->getShaderID(), 1);
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::TESS_CONTROL);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadTesselaionControl)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/tesselaion_control/bad/minimal.tesc", context::ShaderType::TESS_CONTROL);

    // Act
    expectSpecificError([&shader]()
                        { shader.load(); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::COMPILATION_FAILED"));
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::TESS_CONTROL);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderCompute)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/compute/good/minimal.comp", context::ShaderType::COMPUTE);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getContext()->getShaderID(), 1);
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::COMPUTE);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadCompute)
{
    // Arrange
    pipeline::Shader<api::OpenGL> shader("test-datas/shaders/compute/bad/minimal.comp", context::ShaderType::COMPUTE);

    // Act
    expectSpecificError([&shader]()
                        { shader.load(); },
                        cenpy::common::exception::TraceableException<std::runtime_error>("ERROR::SHADER::COMPILATION_FAILED"));
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::COMPUTE);

    shader.free();
}
