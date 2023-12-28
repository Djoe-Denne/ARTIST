#include <string>
#include <graphic/shader/Shader.hpp>
#include <OpenGLComponentTests.hpp>

namespace shader = cenpy::graphic::shader;

class ShaderTest : public OpenGLComponentTest
{
};

TEST_F(ShaderTest, CreateShaderVert)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/vertex/good/minimal.vert", shader::ShaderType::VERTEX);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::VERTEX);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadVert)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/vertex/bad/minimal.vert", shader::ShaderType::VERTEX);

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
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::VERTEX);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderFrag)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/fragment/good/minimal.frag", shader::ShaderType::FRAGMENT);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::FRAGMENT);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadFrag)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/fragment/bad/minimal.frag", shader::ShaderType::FRAGMENT);

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
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::FRAGMENT);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderGeom)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/geometry/good/minimal.geom", shader::ShaderType::GEOMETRY);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::GEOMETRY);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadGeom)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/geometry/bad/minimal.geom", shader::ShaderType::GEOMETRY);

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
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::GEOMETRY);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderTesselaionControl)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/tesselaion_control/good/minimal.tesc", shader::ShaderType::TESS_CONTROL);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::TESS_CONTROL);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadTesselaionControl)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/tesselaion_control/bad/minimal.tesc", shader::ShaderType::TESS_CONTROL);

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
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::TESS_CONTROL);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderCompute)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/compute/good/minimal.comp", shader::ShaderType::COMPUTE);

    // Act
    ASSERT_NO_THROW(shader.load());

    // Assert
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::COMPUTE);

    shader.free();
}

TEST_F(ShaderTest, CreateShaderBadCompute)
{
    // Arrange
    shader::opengl::Shader shader("test-datas/shaders/compute/bad/minimal.comp", shader::ShaderType::COMPUTE);

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
    EXPECT_EQ(shader.getLocation(), 1);
    EXPECT_EQ(shader.getShaderType(), shader::ShaderType::COMPUTE);

    shader.free();
}
