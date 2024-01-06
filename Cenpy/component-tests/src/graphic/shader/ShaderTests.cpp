#include <string>
#include <graphic/shader/Shader.hpp>
#include <OpenGLComponentTests.hpp>
#include <graphic/Api.hpp>
#include <OpenGLComponentTests.hpp>

namespace api = cenpy::graphic::api;
namespace context = cenpy::graphic::context;
namespace shader = cenpy::graphic::shader;

class ShaderTest : public OpenGLComponentTest
{
};

TEST_F(ShaderTest, CreateShaderVert)
{
    // Arrange
    shader::Shader<api::OpenGL> shader("test-datas/shaders/vertex/good/minimal.vert", context::ShaderType::VERTEX);

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
    shader::Shader<api::OpenGL> shader("test-datas/shaders/vertex/bad/minimal.vert", context::ShaderType::VERTEX);

    // Act
    try
    {
        shader.load();
        FAIL() << "Expected an exception to be thrown";
    }
    catch (const std::runtime_error &e)
    {
        std::string errorMsg = e.what();
        EXPECT_NE(errorMsg.find("COMPILATION_FAILED"), std::string::npos) << "Exception message does not contain 'COMPILATION_FAILED'";
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error to be thrown";
    }
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::VERTEX);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderFrag)
{
    // Arrange
    shader::Shader<api::OpenGL> shader("test-datas/shaders/fragment/good/minimal.frag", context::ShaderType::FRAGMENT);

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
    shader::Shader<api::OpenGL> shader("test-datas/shaders/fragment/bad/minimal.frag", context::ShaderType::FRAGMENT);

    // Act
    try
    {
        shader.load();
        FAIL() << "Expected an exception to be thrown";
    }
    catch (const std::runtime_error &e)
    {
        std::string errorMsg = e.what();
        EXPECT_NE(errorMsg.find("COMPILATION_FAILED"), std::string::npos) << "Exception message does not contain 'COMPILATION_FAILED'";
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error to be thrown";
    }
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::FRAGMENT);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderGeom)
{
    // Arrange
    shader::Shader<api::OpenGL> shader("test-datas/shaders/geometry/good/minimal.geom", context::ShaderType::GEOMETRY);

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
    shader::Shader<api::OpenGL> shader("test-datas/shaders/geometry/bad/minimal.geom", context::ShaderType::GEOMETRY);

    // Act
    try
    {
        shader.load();
        FAIL() << "Expected an exception to be thrown";
    }
    catch (const std::runtime_error &e)
    {
        std::string errorMsg = e.what();
        EXPECT_NE(errorMsg.find("COMPILATION_FAILED"), std::string::npos) << "Exception message does not contain 'COMPILATION_FAILED'";
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error to be thrown";
    }
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::GEOMETRY);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderTesselaionControl)
{
    // Arrange
    shader::Shader<api::OpenGL> shader("test-datas/shaders/tesselaion_control/good/minimal.tesc", context::ShaderType::TESS_CONTROL);

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
    shader::Shader<api::OpenGL> shader("test-datas/shaders/tesselaion_control/bad/minimal.tesc", context::ShaderType::TESS_CONTROL);

    // Act
    try
    {
        shader.load();
        FAIL() << "Expected an exception to be thrown";
    }
    catch (const std::runtime_error &e)
    {
        std::string errorMsg = e.what();
        EXPECT_NE(errorMsg.find("COMPILATION_FAILED"), std::string::npos) << "Exception message does not contain 'COMPILATION_FAILED'";
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error to be thrown";
    }
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::TESS_CONTROL);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderCompute)
{
    // Arrange
    shader::Shader<api::OpenGL> shader("test-datas/shaders/compute/good/minimal.comp", context::ShaderType::COMPUTE);

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
    shader::Shader<api::OpenGL> shader("test-datas/shaders/compute/bad/minimal.comp", context::ShaderType::COMPUTE);

    // Act
    try
    {
        shader.load();
        FAIL() << "Expected an exception to be thrown";
    }
    catch (const std::runtime_error &e)
    {
        std::string errorMsg = e.what();
        EXPECT_NE(errorMsg.find("COMPILATION_FAILED"), std::string::npos) << "Exception message does not contain 'COMPILATION_FAILED'";
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error to be thrown";
    }
    // Assert
    EXPECT_EQ(shader.getShaderType(), context::ShaderType::COMPUTE);

    shader.free();
}
